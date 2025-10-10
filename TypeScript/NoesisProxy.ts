import * as UE from 'ue';

/**
 * 创建自动通知的 ViewModel 代理
 *
 * @param target 目标对象
 * @param propertyNames 可选，指定需要监听的属性名列表。如果不指定，则监听所有属性
 * @param enableLogging 可选，是否启用正常消息的日志输出。默认为 false。错误日志始终输出
 * @returns 代理对象，赋值时自动触发 Noesis 通知
 *
 * @example
 * // 监听所有属性，不输出日志
 * const vm = createNoesisProxy(viewModel);
 *
 * // 只监听指定属性，不输出日志
 * const vm = createNoesisProxy(viewModel, ["TestValue", "Count"]);
 *
 * // 监听所有属性，启用日志
 * const vm = createNoesisProxy(viewModel, undefined, true);
 *
 * // 只监听指定属性，启用日志
 * const vm = createNoesisProxy(viewModel, ["TestValue", "Count"], true);
 */
export function createNoesisProxy<T extends UE.Object>(
    target: UE.Object | null | undefined,
    propertyNames?: string[],
    enableLogging: boolean = false
): T | null {
    // 判空处理
    if (!target) {
        console.warn('[NoesisProxy] target 为空，无法创建代理');
        return null;
    }
    
    // 内部类型转换
    const typedTarget = target as T;

    const notifyProps = new Set<string>();

    // 如果指定了属性列表，只监听这些属性
    if (propertyNames && propertyNames.length > 0) {
        propertyNames.forEach(p => notifyProps.add(p));
    } else {
        // 否则，收集所有标记为需要通知的属性
        let proto = Object.getPrototypeOf(typedTarget);
        while (proto && proto !== UE.Object.prototype) {
            if (proto.__noesisNotifyProps) {
                proto.__noesisNotifyProps.forEach((p: string) => notifyProps.add(p));
            }
            proto = Object.getPrototypeOf(proto);
        }

        // 如果没有标记任何属性，默认监听所有 @uproperty 属性
        if (notifyProps.size === 0) {
            // 获取所有可枚举属性作为候选
            for (const key in typedTarget) {
                if (typedTarget.hasOwnProperty(key) && typeof (typedTarget as any)[key] !== 'function') {
                    notifyProps.add(key);
                }
            }
        }
    }

    return new Proxy(typedTarget, {
        set(obj, prop, value) {
            // 必须是字符串属性
            if (typeof prop !== 'string') {
                (obj as any)[prop] = value;
                return true;
            }

            const oldValue = (obj as any)[prop];
            
            // 先设置值到对象
            (obj as any)[prop] = value;

            // 如果是需要通知的属性且值确实改变了，触发通知
            if (notifyProps.has(prop) && oldValue !== value) {
                try {
                    UE.NoesisNotifyHelperLibrary.NotifyPropertyChanged(obj, prop);
                    if (enableLogging) {
                        console.log(`[NoesisProxy] 属性已通知: ${prop} = ${value}`);
                    }
                } catch (error) {
                    console.error(`[NoesisProxy] 通知失败: ${prop}`, error);
                }
            }

            return true;
        },
        
        get(obj, prop) {
            const value = (obj as any)[prop];
            
            // 如果是函数，需要绑定正确的 this
            if (typeof value === 'function') {
                return function(this: any, ...args: any[]) {
                    return value.apply(obj, args);
                };
            }

            // 检测并代理 TArray 和 TMap
            // ⚠️ 重要：先检测 TArray（有 RemoveAt），再检测 TMap（有 Remove 但没有 RemoveAt）
            if (value && typeof value === 'object' && typeof prop === 'string') {
                // 调试日志：显示访问的属性
                if (enableLogging) {
                    console.log(`[NoesisProxy] 访问属性: ${prop}, 类型: ${typeof value}, 在监听列表: ${notifyProps.has(prop)}`);
                }

                if (notifyProps.has(prop)) {
                    // 调试：检查对象有哪些方法
                    if (enableLogging) {
                        const methods = ['Num', 'Add', 'Get', 'Set', 'Remove', 'RemoveAt', 'Keys'];
                        const availableMethods = methods.filter(m => m in value && typeof (value as any)[m] === 'function');
                        console.log(`[NoesisProxy] 属性 ${prop} 可用方法: ${availableMethods.join(', ')}`);
                    }

                    // 优先检测 TArray（通过 RemoveAt 方法明确区分）
                    if (isTArray(value)) {
                        if (enableLogging) {
                            console.log(`[NoesisProxy] ✅ 检测到 TArray 属性: ${prop}`);
                        }
                        return createTArrayProxy(obj, prop, value, enableLogging);
                    }
                    // 再检测 TMap（有 Remove 但没有 RemoveAt）
                    if (isTMap(value)) {
                        if (enableLogging) {
                            console.log(`[NoesisProxy] ✅ 检测到 TMap 属性: ${prop}`);
                        }
                        return createTMapProxy(obj, prop, value, enableLogging);
                    }

                    if (enableLogging) {
                        console.log(`[NoesisProxy] ⚠️ 属性 ${prop} 既不是 TArray 也不是 TMap`);
                    }
                }
            }
            
            return value;
        }
    }) as T;
}

/**
 * 检测是否为 TArray
 * 通过 RemoveAt 方法来区分（TArray 特有）
 * ⚠️ 必须先检测 TArray，因为它有明确的 RemoveAt 方法
 */
function isTArray(obj: any): boolean {
    return obj && 
           typeof obj === 'object' && 
           'Num' in obj && 
           'Add' in obj && 
           'RemoveAt' in obj &&  // TArray 特有的方法
           typeof obj.Num === 'function' &&
           typeof obj.Add === 'function' &&
           typeof obj.RemoveAt === 'function';  // 确保 RemoveAt 是函数
}

/**
 * 检测是否为 TMap
 * 通过 Remove 方法来区分（TMap 有 Remove，但没有 RemoveAt）
 * ⚠️ 注意：Puerts 绑定的 TMap 可能没有暴露 Keys 方法
 */
function isTMap(obj: any): boolean {
    return obj && 
           typeof obj === 'object' && 
           'Num' in obj &&
           'Add' in obj && 
           'Remove' in obj &&  // TMap 有 Remove
           !('RemoveAt' in obj) &&  // ✅ 关键：TMap 没有 RemoveAt
           typeof obj.Num === 'function' &&
           typeof obj.Add === 'function' &&
           typeof obj.Remove === 'function';
}

/**
 * 创建 TArray 的代理
 * 自动拦截数组操作方法并触发相应的 Noesis 通知
 */
function createTArrayProxy(owner: UE.Object, propName: string, tarray: any, enableLogging: boolean = false): any {
    return new Proxy(tarray, {
        get(target, prop) {
            const value = (target as any)[prop];
            
            // 拦截 TArray 的修改方法
            if (typeof value === 'function') {
                return function(this: any, ...args: any[]) {
                    switch (prop) {
                        case 'Add':
                            // 添加元素到末尾
                            const addResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostAdd(owner, propName);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.Add: ${propName}`);
                            }
                            return addResult;
                            
                        case 'Insert':
                            // 插入元素 (value, index)
                            const insertIndex = args[1] !== undefined ? args[1] : 0;
                            const insertResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostInsert(owner, propName, insertIndex);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.Insert: ${propName}[${insertIndex}]`);
                            }
                            return insertResult;

                        case 'RemoveAt':
                            // 移除指定索引的元素
                            const removeIndex = args[0] !== undefined ? args[0] : 0;
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPreRemove(owner, propName, removeIndex);
                            const removeAtResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostRemove(owner, propName, removeIndex);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.RemoveAt: ${propName}[${removeIndex}]`);
                            }
                            return removeAtResult;

                        case 'Remove':
                            // 移除指定值的元素（需要先找到索引）
                            const searchValue = args[0];
                            const findIndex = target.FindIndex ? target.FindIndex(searchValue) : -1;
                            if (findIndex >= 0) {
                                UE.NoesisNotifyHelperLibrary.NotifyArrayPreRemove(owner, propName, findIndex);
                            }
                            const removeResult = value.apply(target, args);
                            if (findIndex >= 0) {
                                UE.NoesisNotifyHelperLibrary.NotifyArrayPostRemove(owner, propName, findIndex);
                                if (enableLogging) {
                                    console.log(`[NoesisProxy] TArray.Remove: ${propName}[${findIndex}]`);
                                }
                            }
                            return removeResult;

                        case 'Empty':
                            // 清空数组
                            const emptyResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostClear(owner, propName);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.Empty: ${propName}`);
                            }
                            return emptyResult;

                        case 'Reset':
                            // 重置数组
                            const resetResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostReset(owner, propName);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.Reset: ${propName}`);
                            }
                            return resetResult;

                        case 'Append':
                            // 批量追加元素
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPreAppend(owner, propName);
                            const appendResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostAppend(owner, propName);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.Append: ${propName}`);
                            }
                            return appendResult;

                        case 'Set':
                            // 设置指定索引的值
                            const setIndex = args[0] !== undefined ? args[0] : 0;
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPreSet(owner, propName, setIndex);
                            const setResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyArrayPostSet(owner, propName, setIndex);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TArray.Set: ${propName}[${setIndex}]`);
                            }
                            return setResult;
                            
                        default:
                            // 其他方法直接调用
                            return value.apply(target, args);
                    }
                };
            }
            
            return value;
        }
    });
}

/**
 * 创建 TMap 的代理
 * 自动拦截 Map 操作方法并触发相应的 Noesis 通知
 *
 * ⚠️ Noesis 要求 TMap 的 Key 必须是 string 类型
 */
function createTMapProxy(owner: UE.Object, propName: string, tmap: any, enableLogging: boolean = false): any {
    return new Proxy(tmap, {
        get(target, prop) {
            const value = (target as any)[prop];
            
            // 拦截 TMap 的修改方法
            if (typeof value === 'function') {
                return function(this: any, ...args: any[]) {
                    switch (prop) {
                        case 'Add':
                        case 'Set':
                            // 添加/设置键值对 (key, value)
                            // Set 是 Add 的别名
                            const key = args[0];

                            // Noesis 要求 Key 必须是 string
                            if (typeof key !== 'string') {
                                console.warn(`[NoesisProxy] TMap.${prop}: Key 必须是 string 类型，当前类型: ${typeof key}，属性: ${propName}`);
                            }

                            const result = value.apply(target, args);
                            const keyStr = String(key !== undefined ? key : '');
                            UE.NoesisNotifyHelperLibrary.NotifyMapPostAdd(owner, propName, keyStr);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TMap.${prop}: ${propName}["${keyStr}"]`);
                            }
                            return result;

                        case 'Remove':
                            // 移除键值对
                            const removeKey = args[0];

                            if (typeof removeKey !== 'string') {
                                console.warn(`[NoesisProxy] TMap.Remove: Key 必须是 string 类型，当前类型: ${typeof removeKey}，属性: ${propName}`);
                            }

                            const removeKeyStr = String(removeKey !== undefined ? removeKey : '');
                            UE.NoesisNotifyHelperLibrary.NotifyMapPreRemove(owner, propName, removeKeyStr);
                            const removeResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyMapPostRemove(owner, propName, removeKeyStr);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TMap.Remove: ${propName}["${removeKeyStr}"]`);
                            }
                            return removeResult;

                        case 'Empty':
                            // 清空 Map
                            const emptyResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyMapPostReset(owner, propName);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TMap.Empty: ${propName}`);
                            }
                            return emptyResult;

                        case 'Reset':
                            // 重置 Map（TMap 可能没有这个方法，但为了兼容性保留）
                            const resetResult = value.apply(target, args);
                            UE.NoesisNotifyHelperLibrary.NotifyMapPostReset(owner, propName);
                            if (enableLogging) {
                                console.log(`[NoesisProxy] TMap.Reset: ${propName}`);
                            }
                            return resetResult;
                            
                        default:
                            // 其他方法直接调用
                            return value.apply(target, args);
                    }
                };
            }
            
            return value;
        }
    });
}

/**
 * 标记需要自动通知的属性装饰器（可选）
 * 如果不使用此装饰器，Proxy 会监听所有属性
 */
export function noesisNotify() {
    return function (target: any, propertyKey: string) {
        if (!target.__noesisNotifyProps) {
            target.__noesisNotifyProps = [];
        }
        target.__noesisNotifyProps.push(propertyKey);
    };
}

