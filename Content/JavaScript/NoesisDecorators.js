"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.NoesisViewModel = exports.noesisNotify = void 0;
const UE = require("ue");
/**
 * 标记需要自动通知的属性
 * 必须与 @uproperty 一起使用
 */
function noesisNotify() {
    return function (target, propertyKey) {
        // 在类原型上记录需要自动通知的属性
        if (!target.__noesisNotifyProps) {
            target.__noesisNotifyProps = [];
        }
        target.__noesisNotifyProps.push(propertyKey);
    };
}
exports.noesisNotify = noesisNotify;
/**
 * NoesisViewModel 基类
 * 所有需要自动属性通知的 ViewModel 都应该继承此类
 */
class NoesisViewModel extends UE.Object {
    constructor() {
        super();
        this.__notifyInitialized = false;
        // 延迟初始化，确保 Puerts 已完成所有属性的创建和初始化
        this.__scheduleNotifyInit();
    }
    /**
     * 延迟初始化通知系统
     */
    __scheduleNotifyInit() {
        // 使用 setTimeout 确保在下一个事件循环中执行
        // 这时 Puerts 已经完成了所有 @uproperty 属性的初始化
        setTimeout(() => {
            this.__initializeNotify();
        }, 0);
    }
    /**
     * 初始化自动通知系统
     * 重写所有标记了 @noesisNotify 的属性
     */
    __initializeNotify() {
        if (this.__notifyInitialized) {
            return;
        }
        this.__notifyInitialized = true;
        // 收集所有需要处理的属性（包括继承链上的）
        const notifyProps = [];
        let proto = Object.getPrototypeOf(this);
        while (proto && proto !== UE.Object.prototype) {
            if (proto.__noesisNotifyProps) {
                notifyProps.push(...proto.__noesisNotifyProps);
            }
            proto = Object.getPrototypeOf(proto);
        }
        // 为每个属性设置自动通知
        for (const propName of notifyProps) {
            this.__setupPropertyNotify(propName);
        }
        console.log(`[NoesisViewModel] Auto-notify initialized for properties: [${notifyProps.join(', ')}]`);
    }
    /**
     * 为单个属性设置自动通知
     */
    __setupPropertyNotify(propName) {
        const backingField = `__backing_${propName}`;
        try {
            // 1. 获取原始属性描述符（Puerts 创建的）
            const originalDescriptor = Object.getOwnPropertyDescriptor(this, propName) ||
                Object.getOwnPropertyDescriptor(Object.getPrototypeOf(this), propName);
            // 2. 保存当前值到备份字段
            const currentValue = this[propName];
            this[backingField] = currentValue;
            // 3. 重新定义属性为 getter/setter
            Object.defineProperty(this, propName, {
                get: function () {
                    return this[backingField];
                },
                set: function (newValue) {
                    const oldValue = this[backingField];
                    // 避免重复通知
                    if (oldValue === newValue) {
                        return;
                    }
                    // 更新备份值（JavaScript 端）
                    this[backingField] = newValue;
                    // 同步到 C++ 端（如果有原始 setter）
                    if (originalDescriptor?.set) {
                        originalDescriptor.set.call(this, newValue);
                    }
                    else {
                        // 如果没有原始 setter，尝试直接赋值到原始属性
                        // 这种情况下需要临时绕过我们的 setter
                        this.__directSetProperty(propName, newValue);
                    }
                    // 自动通知 Noesis
                    this.__notifyPropertyChanged(propName);
                },
                enumerable: true,
                configurable: true
            });
        }
        catch (error) {
            console.error(`[NoesisViewModel] Failed to setup auto-notify for property '${propName}':`, error);
        }
    }
    /**
     * 直接设置属性值（绕过我们的 setter）
     */
    __directSetProperty(propName, value) {
        const backingField = `__backing_${propName}`;
        const tempDescriptor = Object.getOwnPropertyDescriptor(this, propName);
        try {
            // 临时移除我们的 setter
            delete this[propName];
            // 直接赋值（会调用 Puerts 的机制）
            this[propName] = value;
            // 恢复我们的 setter
            if (tempDescriptor) {
                Object.defineProperty(this, propName, tempDescriptor);
            }
        }
        catch (error) {
            console.error(`[NoesisViewModel] Failed to direct set property '${propName}':`, error);
            // 恢复 setter（防止属性丢失）
            if (tempDescriptor) {
                Object.defineProperty(this, propName, tempDescriptor);
            }
        }
    }
    /**
     * 内部通知方法
     */
    __notifyPropertyChanged(propName) {
        try {
            UE.NoesisNotifyHelperLibrary.NotifyPropertyChanged(this, propName);
            console.log(`[NoesisViewModel] Property '${propName}' changed and notified`);
        }
        catch (error) {
            console.error(`[NoesisViewModel] Failed to notify property '${propName}':`, error);
        }
    }
    /**
     * 手动触发属性通知（兼容旧代码）
     * @param propName 属性名称
     */
    NotifyPropertyChanged(propName) {
        this.__notifyPropertyChanged(propName);
    }
    /**
     * 批量设置属性值并通知
     * @param properties 属性键值对
     */
    SetProperties(properties) {
        for (const [key, value] of Object.entries(properties)) {
            this[key] = value;
        }
    }
    /**
     * 强制重新初始化通知系统（调试用）
     */
    __ForceReinitNotify() {
        this.__notifyInitialized = false;
        this.__initializeNotify();
    }
}
exports.NoesisViewModel = NoesisViewModel;
//# sourceMappingURL=NoesisDecorators.js.map