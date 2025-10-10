import * as UE from 'ue';
import {ScriptCallHandler} from "./ScriptCallHandler";
import { BindingHelper } from './BindingHelper';

/**
 * 上下文管理器 (单例)
 * 负责管理全局游戏上下文和子系统
 */
export class ContextManager {
    public UE_GameInstance: UE.NoesisDemoGameInstance;
    private ScriptCall : ScriptCallHandler;

    Init() {
        this.ScriptCall = new ScriptCallHandler(this.UE_GameInstance);
        let UE_ScriptSub = UE.NoesisDemoSubLibrary.GetPuertsSub(this.UE_GameInstance);
        if(UE_ScriptSub != null){
            UE_ScriptSub.OnCallTypeScript.Bind(
                BindingHelper.bindCallback2(this.ScriptCall,this.ScriptCall.CallOnFunc)
            );
        }
    }
}

// 直接导出实例
export const GameContext = new ContextManager();