"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.NoesisViewModelFactory = void 0;
exports.createViewModel = createViewModel;
exports.createViewModelWithProperties = createViewModelWithProperties;
const UE = require("ue");
const NoesisDecorators_1 = require("./NoesisDecorators");
/**
 * NoesisGUI ViewModel 工厂
 *
 * 提供统一的 ViewModel 创建和初始化接口
 * 确保自动通知系统正确初始化
 */
class NoesisViewModelFactory {
    /**
     * 创建 ViewModel 实例并初始化自动通知系统
     *
     * @template T ViewModel 类型
     * @param classPath UE 类路径，例如 "/Game/BluePrints/TypeScript/TS_NoesisViewMode.TS_NoesisViewMode_C"
     * @returns 初始化完成的 ViewModel 实例
     *
     * 使用示例:
     * ```typescript
     * const viewModel = NoesisViewModelFactory.Create<TS_NoesisViewMode>(
     *     "/Game/BluePrints/TypeScript/TS_NoesisViewMode.TS_NoesisViewMode_C"
     * );
     * ```
     */
    static Create(classPath) {
        console.log(`[NoesisViewModelFactory] Creating ViewModel from class: ${classPath}`);
        try {
            // 1. 加载 UE 类
            const ViewModeClass = UE.Class.Load(classPath);
            if (!ViewModeClass) {
                throw new Error(`Failed to load UE class: ${classPath}`);
            }
            console.log(`[NoesisViewModelFactory] Successfully loaded class: ${ViewModeClass.GetName()}`);
            // 2. 创建实例
            const instance = UE.NewObject(ViewModeClass);
            if (!instance) {
                throw new Error(`Failed to create instance from class: ${classPath}`);
            }
            console.log(`[NoesisViewModelFactory] Created instance: ${instance.constructor.name}`);
            // 3. 确保实例是 NoesisViewModel 的子类
            if (!(instance instanceof NoesisDecorators_1.NoesisViewModel)) {
                console.warn(`[NoesisViewModelFactory] Warning: ${classPath} is not a NoesisViewModel subclass. Auto-notify may not work.`);
            }
            // 4. 强制初始化自动通知系统（如果需要）
            // 通常 NoesisViewModel 构造函数会自动处理，但这里提供兜底机制
            setTimeout(() => {
                if (instance && typeof instance.__debugReinitializeAutoNotify === 'function') {
                    console.log(`[NoesisViewModelFactory] Ensuring auto-notify is initialized for: ${instance.constructor.name}`);
                }
            }, 10);
            console.log(`[NoesisViewModelFactory] Successfully created and initialized ViewModel`);
            return instance;
        }
        catch (error) {
            console.error(`[NoesisViewModelFactory] Error creating ViewModel:`, error);
            throw error;
        }
    }
    /**
     * 批量创建多个 ViewModel 实例
     *
     * @param classPaths 类路径数组
     * @returns ViewModel 实例数组
     */
    static CreateMultiple(classPaths) {
        console.log(`[NoesisViewModelFactory] Creating multiple ViewModels:`, classPaths);
        const instances = [];
        for (const classPath of classPaths) {
            try {
                const instance = this.Create(classPath);
                instances.push(instance);
            }
            catch (error) {
                console.error(`[NoesisViewModelFactory] Failed to create ViewModel ${classPath}:`, error);
                // 继续创建其他实例，不中断整个流程
            }
        }
        console.log(`[NoesisViewModelFactory] Successfully created ${instances.length}/${classPaths.length} ViewModels`);
        return instances;
    }
    /**
     * 创建 ViewModel 并设置初始属性值
     *
     * @template T ViewModel 类型
     * @param classPath UE 类路径
     * @param initialProperties 初始属性值对象
     * @returns 初始化完成的 ViewModel 实例
     *
     * 使用示例:
     * ```typescript
     * const viewModel = NoesisViewModelFactory.CreateWithProperties<TS_NoesisViewMode>(
     *     "/Game/.../TS_NoesisViewMode_C",
     *     { TestValue: "Initial Value", NormalValue: 123 }
     * );
     * ```
     */
    static CreateWithProperties(classPath, initialProperties) {
        console.log(`[NoesisViewModelFactory] Creating ViewModel with initial properties:`, initialProperties);
        const instance = this.Create(classPath);
        // 延迟设置属性，确保自动通知系统已经初始化
        setTimeout(() => {
            for (const [key, value] of Object.entries(initialProperties)) {
                try {
                    instance[key] = value;
                    console.log(`[NoesisViewModelFactory] Set initial property: ${key} = ${value}`);
                }
                catch (error) {
                    console.error(`[NoesisViewModelFactory] Failed to set property ${key}:`, error);
                }
            }
        }, 20);
        return instance;
    }
    /**
     * 检查类是否支持自动通知
     *
     * @param classPath UE 类路径
     * @returns 是否支持自动通知
     */
    static IsAutoNotifySupported(classPath) {
        try {
            const ViewModeClass = UE.Class.Load(classPath);
            if (!ViewModeClass)
                return false;
            // 创建临时实例检查
            const tempInstance = UE.NewObject(ViewModeClass);
            const isSupported = tempInstance instanceof NoesisDecorators_1.NoesisViewModel;
            console.log(`[NoesisViewModelFactory] Auto-notify supported for ${classPath}: ${isSupported}`);
            return isSupported;
        }
        catch (error) {
            console.error(`[NoesisViewModelFactory] Error checking auto-notify support:`, error);
            return false;
        }
    }
}
exports.NoesisViewModelFactory = NoesisViewModelFactory;
/**
 * 便捷函数：创建 ViewModel 实例
 *
 * @template T ViewModel 类型
 * @param classPath UE 类路径
 * @returns ViewModel 实例
 */
function createViewModel(classPath) {
    return NoesisViewModelFactory.Create(classPath);
}
/**
 * 便捷函数：创建 ViewModel 并设置属性
 *
 * @template T ViewModel 类型
 * @param classPath UE 类路径
 * @param properties 初始属性
 * @returns ViewModel 实例
 */
function createViewModelWithProperties(classPath, properties) {
    return NoesisViewModelFactory.CreateWithProperties(classPath, properties);
}
//# sourceMappingURL=NoesisViewModelFactory.js.map