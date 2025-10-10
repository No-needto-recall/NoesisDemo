"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.NoesisPropertyHelper = void 0;
exports.setNoesisProperty = setNoesisProperty;
const UE = require("ue");
/**
 * Noesis 属性辅助类
 * 提供简洁的方法来设置属性并自动触发通知
 */
class NoesisPropertyHelper {
    /**
     * 设置属性并自动调用 NotifyPropertyChanged
     *
     * @param instance 对象实例
     * @param propertyName 属性名
     * @param newValue 新值
     * @param options 选项
     */
    static set(instance, propertyName, newValue, options = {}) {
        const { silent = false, forceNotify = false } = options;
        const oldValue = instance[propertyName];
        // 判断是否需要通知
        let shouldNotify = forceNotify;
        if (!shouldNotify) {
            const valueType = typeof newValue;
            if (valueType === 'object') {
                shouldNotify = true;
            }
            else {
                shouldNotify = oldValue !== newValue;
            }
        }
        // 设置值
        instance[propertyName] = newValue;
        // 触发通知
        if (shouldNotify) {
            try {
                UE.NoesisNotifyHelperLibrary.NotifyPropertyChanged(instance, propertyName);
                if (!silent) {
                    const valueType = typeof newValue;
                    console.log(`[NoesisProperty] "${propertyName}" 已更新: ${valueType === 'object' ? '[Object]' : oldValue} -> ${valueType === 'object' ? '[Object]' : newValue}`);
                }
            }
            catch (error) {
                console.error(`[NoesisProperty] 通知失败: ${propertyName}`, error);
            }
        }
    }
    /**
     * 批量设置多个属性
     */
    static setMultiple(instance, properties, options = {}) {
        for (const [key, value] of Object.entries(properties)) {
            this.set(instance, key, value, options);
        }
    }
}
exports.NoesisPropertyHelper = NoesisPropertyHelper;
/**
 * 简化版的 set 函数（推荐使用）
 */
function setNoesisProperty(instance, propertyName, newValue, silent = false) {
    NoesisPropertyHelper.set(instance, propertyName, newValue, { silent });
}
//# sourceMappingURL=NoesisPropertyHelper.js.map