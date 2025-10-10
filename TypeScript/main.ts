import * as cpp from 'cpp'
import * as UE from 'ue';
import { argv } from 'puerts';
import {GameContext} from "./ContextManager";
import {ScriptCallHandler} from "./ScriptCallHandler";

/**
 * PuerTS 入口文件
 *
 * TS 初始化工作可以在这里完成
 */

/************** 初始化 TS 工程 ***************/
(
    async function main() {
        await init();
    }
)();

/************** 初始化 TS 工程 ***************/

/**
 * C++ GameInstance 在创建 js 虚拟机后调用
 */
async function init() {
    console.log("Init Start");
    let gameInstance = (argv.getByName("GameInstance") as UE.NoesisDemoGameInstance);
    GameContext.UE_GameInstance = gameInstance;
    GameContext.Init();
    gameInstance.OnGameInstanceShutdown.Add(shutdown);
    console.log("Init Down");
}

/**
 * C++ GameInstance 在杀死 js 虚拟机前调用
 */
async function shutdown() {
    console.log("shutdown");
}
