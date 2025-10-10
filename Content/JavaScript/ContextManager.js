"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.GameContext = exports.ContextManager = void 0;
const UE = require("ue");
const ScriptCallHandler_1 = require("./ScriptCallHandler");
const BindingHelper_1 = require("./BindingHelper");
/**
 * 上下文管理器 (单例)
 * 负责管理全局游戏上下文和子系统
 */
class ContextManager {
    Init() {
        this.ScriptCall = new ScriptCallHandler_1.ScriptCallHandler(this.UE_GameInstance);
        let UE_ScriptSub = UE.NoesisDemoSubLibrary.GetPuertsSub(this.UE_GameInstance);
        if (UE_ScriptSub != null) {
            UE_ScriptSub.OnCallTypeScript.Bind(BindingHelper_1.BindingHelper.bindCallback2(this.ScriptCall, this.ScriptCall.CallOnFunc));
        }
    }
}
exports.ContextManager = ContextManager;
// 直接导出实例
exports.GameContext = new ContextManager();
//# sourceMappingURL=ContextManager.js.map