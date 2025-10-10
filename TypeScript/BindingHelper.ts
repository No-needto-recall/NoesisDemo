import * as UE from 'ue';

/**
 * 回调绑定辅助类
 * 提供统一的方法来正确绑定回调，保持this上下文
 */
export class BindingHelper {
    /**
     * 绑定单参数回调
     */
    static bindCallback<T>(
        target: any, 
        method: (arg: T) => void
    ): (arg: T) => void {
        return (arg: T) => method.call(target, arg);
    }
    
    /**
     * 绑定双参数回调
     */
    static bindCallback2<T1, T2>(
        target: any, 
        method: (arg1: T1, arg2: T2) => void
    ): (arg1: T1, arg2: T2) => void {
        return (arg1: T1, arg2: T2) => method.call(target, arg1, arg2);
    }
    
    /**
     * 绑定无参数回调
     */
    static bindCallbackNoArgs(
        target: any, 
        method: () => void
    ): () => void {
        return () => method.call(target);
    }
    
    /**
     * 绑定接收 InstancedStruct 参数的回调
     */
    static bindCallbackInstancedStruct(
        target: any,
        method: (data: UE.InstancedStruct) => void
    ): (data: UE.InstancedStruct) => void {
        return (data: UE.InstancedStruct) => method.call(target, data);
    }
    
    /**
     * 使用bind方法绑定（替代方案）
     * 注意：这种方式创建的函数无法解绑
     */
    static bindMethod<T extends (...args: any[]) => any>(
        target: any,
        method: T
    ): T {
        return method.bind(target) as T;
    }
}