"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const puerts_1 = require("puerts");
const ContextManager_1 = require("./ContextManager");
/**
 * PuerTS 入口文件
 *
 * TS 初始化工作可以在这里完成
 */
/************** 初始化 TS 工程 ***************/
(async function main() {
    await init();
})();
/************** 初始化 TS 工程 ***************/
/**
 * C++ GameInstance 在创建 js 虚拟机后调用
 */
async function init() {
    console.log("Init Start");
    let gameInstance = puerts_1.argv.getByName("GameInstance");
    ContextManager_1.GameContext.UE_GameInstance = gameInstance;
    ContextManager_1.GameContext.Init();
    gameInstance.OnGameInstanceShutdown.Add(shutdown);
    console.log("Init Down");
}
/**
 * C++ GameInstance 在杀死 js 虚拟机前调用
 */
async function shutdown() {
    console.log("shutdown");
}
//# sourceMappingURL=main.js.map