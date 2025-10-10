"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.NoesisGUIExamples = void 0;
const UE = require("ue");
const puerts = require("ue");
const ue_1 = require("ue");
/**
 * NoesisGUI 使用示例集合
 * 展示使用新版本便捷成员函数创建和管理 DataContext 的各种方法
 */
class NoesisGUIExamples {
    /**
     * 多层级 ViewMode 示例（改写版）
     * 使用新的便捷成员函数创建复杂的 ViewMode 结构
     *
     * @param gameInstance - 游戏实例
     * @param xamlPath - XAML 资源路径
     * @returns 创建的 NoesisInstance
     */
    static CreateMultiViewModeExample(gameInstance, xamlPath) {
        console.log("=== 多层级 ViewMode 示例 (新版本) ===");
        // 加载 XAML 资源
        const xamlAsset = UE.Object.Load(xamlPath);
        if (!xamlAsset) {
            console.error("Failed to load XAML asset:", xamlPath);
            return null;
        }
        // 获取玩家控制器
        const playerController = UE.GameplayStatics.GetPlayerController(gameInstance, 0);
        if (!playerController) {
            console.error("Failed to get player controller");
            return null;
        }
        // 创建根 DataContext
        const rootDataContext = puerts.NewObject(UE.NoesisViewModeNode.StaticClass());
        if (!rootDataContext) {
            console.error("Failed to create root DataContext");
            return null;
        }
        // 使用新的便捷函数创建和配置子 ViewMode
        this.SetupPlayerViewMode(rootDataContext);
        this.SetupEconomyViewMode(rootDataContext);
        this.SetupBattleViewMode(rootDataContext);
        console.log("多 ViewMode 数据结构创建完成（新版本）:");
        console.log("- 根 DataContext: 已创建");
        console.log("- 子 ViewMode: Player, Economy, Battle");
        // 创建 NoesisInstance 并添加到视口
        const guiInstance = UE.NoesisViewModeFunctionLibrary.CreateNoesisInstance(gameInstance, xamlAsset, playerController, rootDataContext);
        if (guiInstance) {
            guiInstance.AddToViewport(0);
            UE.WidgetBlueprintLibrary.SetInputMode_GameAndUIEx(playerController, guiInstance, ue_1.EMouseLockMode.DoNotLock, true, false);
            guiInstance.SetKeyboardFocus();
            // 测试事件触发
            this.TestEventTrigger(rootDataContext);
            console.log("多层级 ViewMode 示例创建成功");
            return guiInstance;
        }
        console.error("Failed to create NoesisInstance");
        return null;
    }
    /**
     * 设置玩家 ViewMode（使用新的便捷函数）
     */
    static SetupPlayerViewMode(rootDataContext) {
        // 使用 AddSubViewMode 创建子 ViewMode
        const playerViewMode = rootDataContext.AddSubViewMode("Player");
        if (!playerViewMode) {
            console.error("Failed to create Player ViewMode");
            return;
        }
        // 使用便捷的 SetString 函数
        playerViewMode.SetString("PlayerName", "Handler IceAD [Player]");
        playerViewMode.SetString("PlayerTitle", "最强塔防指挥官");
        playerViewMode.SetInt32("PlayerLevel", 25);
        // 使用 AddEventProperty 创建事件
        const eventProperty = playerViewMode.AddEventProperty("EventTest");
        if (eventProperty) {
            console.log("- Player ViewMode: 属性和事件设置完成");
        }
    }
    /**
     * 设置经济系统 ViewMode（使用新的便捷函数）
     */
    static SetupEconomyViewMode(rootDataContext) {
        const economyViewMode = rootDataContext.AddSubViewMode("Economy");
        if (!economyViewMode) {
            console.error("Failed to create Economy ViewMode");
            return;
        }
        // 使用便捷的 SetInt32 函数
        economyViewMode.SetInt32("Money", 1000);
        economyViewMode.SetInt32("Score", 2500);
        economyViewMode.SetInt32("Gems", 150);
        // 添加经济相关的字符串信息
        economyViewMode.SetString("CurrencyName", "金币");
        economyViewMode.SetString("ScoreRank", "A级指挥官");
        console.log("- Economy ViewMode: 属性设置完成");
    }
    /**
     * 设置战斗属性 ViewMode（使用新的便捷函数）
     */
    static SetupBattleViewMode(rootDataContext) {
        const battleViewMode = rootDataContext.AddSubViewMode("Battle");
        if (!battleViewMode) {
            console.error("Failed to create Battle ViewMode");
            return;
        }
        // 使用便捷的 SetFloat 函数
        battleViewMode.SetFloat("Speed", 15.75);
        battleViewMode.SetFloat("Damage", 85.5);
        battleViewMode.SetFloat("Defense", 42.8);
        battleViewMode.SetFloat("CriticalRate", 0.15);
        // 添加战斗相关信息
        battleViewMode.SetString("WeaponType", "量子炮台");
        battleViewMode.SetInt32("KillCount", 1337);
        console.log("- Battle ViewMode: 属性设置完成");
    }
    /**
     * 测试事件触发
     */
    static TestEventTrigger(rootDataContext) {
        // 使用 GetSubViewMode 获取子 ViewMode
        const playerViewMode = rootDataContext.GetSubViewMode("Player");
        if (playerViewMode) {
            // 使用 GetEventProperty 获取事件属性
            const eventProperty = playerViewMode.GetEventProperty("EventTest");
            if (eventProperty) {
                eventProperty.TriggerViewEvent();
                console.log("- 事件触发测试完成");
            }
        }
    }
    /**
     * 简单示例 - 展示最基本的使用方式
     *
     * @param gameInstance - 游戏实例
     * @param xamlPath - XAML 资源路径
     * @returns 创建的 NoesisInstance
     */
    static CreateSimpleExample(gameInstance, xamlPath) {
        console.log("=== 简单示例 ===");
        const xamlAsset = UE.Object.Load(xamlPath);
        const playerController = UE.GameplayStatics.GetPlayerController(gameInstance, 0);
        if (!xamlAsset || !playerController) {
            console.error("Failed to load resources for simple example");
            return null;
        }
        // 创建简单的 DataContext
        const dataContext = puerts.NewObject(UE.NoesisViewModeNode.StaticClass());
        // 使用最简单的方式设置属性
        dataContext.SetString("Title", "简单示例");
        dataContext.SetString("Message", "这是一个使用新版本函数的简单示例");
        dataContext.SetInt32("Counter", 42);
        dataContext.SetFloat("Progress", 0.8);
        // 创建 GUI 实例
        const guiInstance = UE.NoesisViewModeFunctionLibrary.CreateNoesisInstance(gameInstance, xamlAsset, playerController, dataContext);
        if (guiInstance) {
            guiInstance.AddToViewport(0);
            console.log("简单示例创建成功");
            return guiInstance;
        }
        return null;
    }
    /**
     * 工厂函数示例 - 展示使用工厂类和子系统的方式
     *
     * @param gameInstance - 游戏实例
     * @param xamlPath - XAML 资源路径
     * @returns 创建的 NoesisInstance
     */
    static CreateWithFactoryExample(gameInstance, xamlPath) {
        console.log("=== 工厂函数示例 ===");
        const playerController = UE.GameplayStatics.GetPlayerController(gameInstance, 0);
        if (!playerController) {
            console.error("Failed to get player controller");
            return null;
        }
        // 获取 NoesisGUI 子系统
        const noesisGUISub = UE.NoesisViewModeFunctionLibrary.GetNoesisGUISubsystem(gameInstance);
        if (!noesisGUISub) {
            console.error("Failed to get NoesisGUI subsystem");
            return null;
        }
        // 使用子系统加载和缓存 XAML
        const xamlAsset = noesisGUISub.LoadAndCacheXaml(xamlPath);
        if (!xamlAsset) {
            console.error("Failed to load XAML through subsystem");
            return null;
        }
        // 使用工厂函数创建配置化的 DataContext
        // 注意：在实际使用中，这些 Map 和 Array 类型可能需要根据具体的 PuerTS 类型定义进行调整
        // 这里使用简化的方式创建 DataContext
        const dataContext = UE.NoesisViewModeDataContextFactory.CreateBaseViewMode(gameInstance);
        if (!dataContext) {
            console.error("Failed to create base DataContext");
            return null;
        }
        // 手动添加属性（使用新的便捷函数）
        dataContext.SetString("AppName", "塔防指挥部");
        dataContext.SetString("Version", "v2.1.0");
        dataContext.SetString("Author", "IceAD Studio");
        dataContext.SetInt32("MaxLevel", 100);
        dataContext.SetInt32("CurrentWave", 15);
        dataContext.SetInt32("TotalEnemies", 500);
        dataContext.SetFloat("GameSpeed", 1.5);
        dataContext.SetFloat("Difficulty", 0.75);
        dataContext.SetFloat("MasterVolume", 0.8);
        dataContext.AddEventProperty("OnStartGame");
        dataContext.AddEventProperty("OnPauseGame");
        dataContext.AddEventProperty("OnSettingsOpen");
        // 直接使用 NoesisGUI 函数库创建实例（简化版本）
        const guiInstance = UE.NoesisViewModeFunctionLibrary.CreateNoesisInstance(gameInstance, xamlAsset, playerController, dataContext);
        if (guiInstance) {
            guiInstance.AddToViewport(0);
            console.log("工厂函数示例创建成功");
            console.log("- 使用了 NoesisGUI 子系统");
            console.log("- 使用了工厂函数创建 DataContext");
            console.log("- 实例已注册到子系统中");
            // 打印子系统状态
            noesisGUISub.PrintSubsystemStatus();
            return guiInstance;
        }
        return null;
    }
    /**
     * 展示属性管理功能的示例
     */
    static DemoPropertyManagement() {
        console.log("=== 属性管理示例 ===");
        // 创建一个测试用的 ViewMode
        const testViewMode = puerts.NewObject(UE.NoesisViewModeNode.StaticClass());
        // 添加各种类型的属性
        testViewMode.SetString("PlayerName", "测试玩家");
        testViewMode.SetInt32("Level", 10);
        testViewMode.SetFloat("Experience", 2500.5);
        testViewMode.AddEventProperty("OnLevelUp");
        // 展示属性查询功能
        console.log("当前属性列表:", testViewMode.GetAllPropertyNames());
        console.log("玩家名称:", testViewMode.GetString("PlayerName"));
        console.log("玩家等级:", testViewMode.GetInt32("Level"));
        console.log("经验值:", testViewMode.GetFloat("Experience"));
        // 展示属性检查功能
        console.log("是否有 PlayerName 属性:", testViewMode.HasProperty("PlayerName", "String"));
        console.log("是否有 OnLevelUp 事件:", testViewMode.HasProperty("OnLevelUp", "Event"));
        console.log("是否有不存在的属性:", testViewMode.HasProperty("NotExist", "All"));
        // 展示属性修改
        testViewMode.SetInt32("Level", 11);
        console.log("升级后等级:", testViewMode.GetInt32("Level"));
        // 展示属性移除
        testViewMode.RemoveProperty("Experience", "Float");
        console.log("移除经验值后的属性列表:", testViewMode.GetAllPropertyNames());
        console.log("属性管理示例演示完成");
    }
}
exports.NoesisGUIExamples = NoesisGUIExamples;
//# sourceMappingURL=NoesisGUIExamples.js.map