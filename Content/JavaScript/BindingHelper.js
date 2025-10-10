"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.BindingHelper = void 0;
/**
 * 回调绑定辅助类
 * 提供统一的方法来正确绑定回调，保持this上下文
 */
class BindingHelper {
    /**
     * 绑定单参数回调
     */
    static bindCallback(target, method) {
        return (arg) => method.call(target, arg);
    }
    /**
     * 绑定双参数回调
     */
    static bindCallback2(target, method) {
        return (arg1, arg2) => method.call(target, arg1, arg2);
    }
    /**
     * 绑定无参数回调
     */
    static bindCallbackNoArgs(target, method) {
        return () => method.call(target);
    }
    /**
     * 绑定接收 InstancedStruct 参数的回调
     */
    static bindCallbackInstancedStruct(target, method) {
        return (data) => method.call(target, data);
    }
    /**
     * 使用bind方法绑定（替代方案）
     * 注意：这种方式创建的函数无法解绑
     */
    static bindMethod(target, method) {
        return method.bind(target);
    }
}
exports.BindingHelper = BindingHelper;
//# sourceMappingURL=BindingHelper.js.map