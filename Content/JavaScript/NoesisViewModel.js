"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.NoesisViewModel = void 0;
exports.noesisProperty = noesisProperty;
const UE = require("ue");
/**
 * Noesis ViewModel 基类
 * 提供自动属性通知功能
 */
class NoesisViewModel extends UE.Object {
    constructor() {
        super(...arguments);
        // 存储需要通知的属性列表
        this.__noesisTrackedProperties = new Set();
    }
    /**
     * 设置属性值并自动触发通知
     * @param propertyName 属性名
     * @param newValue 新值
     * @param silent 是否静默（不输出日志）
     */
    setProperty(propertyName, newValue, silent = false) {
        const oldValue = this[propertyName];
        // 判断是否需要通知
        let shouldNotify = false;
        const valueType = typeof newValue;
        if (valueType === 'object') {
            shouldNotify = true;
        }
        else {
            shouldNotify = oldValue !== newValue;
        }
        // 设置值
        this[propertyName] = newValue;
        // 触发通知
        if (shouldNotify) {
            try {
                UE.NoesisNotifyHelperLibrary.NotifyPropertyChanged(this, propertyName);
                if (!silent) {
                    console.log(`[NoesisVM] "${propertyName}" 已更新: ${valueType === 'object' ? '[Object]' : oldValue} -> ${valueType === 'object' ? '[Object]' : newValue}`);
                }
            }
            catch (error) {
                console.error(`[NoesisVM] 通知失败: ${propertyName}`, error);
            }
        }
    }
    /**
     * 批量设置属性
     */
    setProperties(properties, silent = false) {
        for (const [key, value] of Object.entries(properties)) {
            this.setProperty(key, value, silent);
        }
    }
    /**
     * 手动触发属性通知
     */
    notifyPropertyChanged(propertyName) {
        try {
            UE.NoesisNotifyHelperLibrary.NotifyPropertyChanged(this, propertyName);
            console.log(`[NoesisVM] 手动通知属性变更: ${propertyName}`);
        }
        catch (error) {
            console.error(`[NoesisVM] 手动通知失败: ${propertyName}`, error);
        }
    }
}
exports.NoesisViewModel = NoesisViewModel;
/**
 * 标记属性为可跟踪（可选的装饰器，用于文档目的）
 */
function noesisProperty() {
    return function (target, propertyKey) {
        // 仅用于标记，实际功能由 setProperty 方法实现
        // 可以在这里收集元数据，但不执行运行时逻辑
    };
}
//# sourceMappingURL=NoesisViewModel.js.map