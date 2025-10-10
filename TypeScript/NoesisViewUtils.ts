import * as UE from 'ue';

/**
 * NoesisGUI 视图管理工具类
 * 提供创建和管理 NoesisGUI Instance 和 ViewMode 的静态工具函数
 */
export class NoesisViewUtils {
    /**
     * 创建 ViewMode 实例
     * @param viewModeClassPath ViewMode 类路径
     * @returns ViewMode 实例或 null
     */
    public static createViewMode(viewModeClassPath: string): UE.Object | null {
        const ViewModeClass = UE.Class.Load(viewModeClassPath);
        if (!ViewModeClass) {
            console.error("Failed to load Class Asset:", viewModeClassPath);
            return null;
        }
        return UE.NewObject(ViewModeClass);
    }

    /**
     * 使用已创建的 ViewMode 创建 NoesisInstance
     * @param xamlPath XAML 文件路径
     * @param viewMode 已创建的 ViewMode 实例
     * @param gameInstance 游戏实例
     * @param playerController 可选的玩家控制器
     * @returns NoesisInstance 或 null
     */
    public static createNoesisInstance(
        xamlPath: string,
        viewMode: UE.Object,
        gameInstance: UE.GameInstance,
        playerController?: UE.PlayerController
    ): UE.NoesisViewModeInstance | null {
        // 加载 XAML 资源
        const xamlAsset = UE.Object.Load(xamlPath) as UE.NoesisXaml;
        if (!xamlAsset) {
            console.error("Failed to load XAML asset:", xamlPath);
            return null;
        }

        // 获取玩家控制器
        if (!playerController) {
            playerController = UE.GameplayStatics.GetPlayerController(gameInstance, 0);
            if (!playerController) {
                console.error("Failed to get player controller");
                return null;
            }
        }

        // 创建 NoesisInstance，使用传入的 viewMode
        const guiInstance = UE.NoesisViewModeFunctionLibrary.CreateNoesisInstance(
            gameInstance,
            xamlAsset,
            playerController,
            viewMode
        );

        if (guiInstance) {
            console.log("NoesisInstance created successfully");
            return guiInstance;
        } else {
            console.error("Failed to create NoesisInstance");
            return null;
        }
    }

    /**
     * 将 NoesisInstance 添加到视口并设置输入
     * @param instance NoesisInstance 实例
     * @param gameInstance 游戏实例（用于获取玩家控制器）
     * @param zOrder 可选的 Z 顺序
     * @returns 是否成功添加
     */
    public static attachToViewport(
        instance: UE.NoesisViewModeInstance,
        gameInstance: UE.GameInstance,
        zOrder: number = 0
    ): boolean {
        if (!instance) {
            console.error("Invalid NoesisInstance");
            return false;
        }

        // 获取玩家控制器
        const playerController = UE.GameplayStatics.GetPlayerController(gameInstance, 0);
        if (!playerController) {
            console.error("Failed to get player controller");
            return false;
        }

        // 添加到视口
        instance.AddToViewport(zOrder);

        // 设置输入模式为 UI 模式
        UE.WidgetBlueprintLibrary.SetInputMode_UIOnlyEx(
            playerController,
            instance,
            UE.EMouseLockMode.DoNotLock
        );

        // 设置键盘焦点
        instance.SetKeyboardFocus();

        console.log("NoesisInstance attached to viewport successfully");
        return true;
    }

    /**
     * 兼容旧版本的 LoadNoesisView 方法
     * 内部使用新的分离方法实现
     * @param xamlPath XAML 文件路径
     * @param viewModeClassPath ViewMode 类路径
     * @param gameInstance 游戏实例
     * @returns NoesisInstance 或 null
     */
    public static loadNoesisView(
        xamlPath: string,
        viewModeClassPath: string,
        gameInstance: UE.GameInstance
    ): UE.NoesisViewModeInstance | null {
        // 阶段1：创建 ViewMode（Constructor 被调用）
        const viewMode = NoesisViewUtils.createViewMode(viewModeClassPath);
        if (!viewMode) {
            return null;
        }

        // 阶段2：创建 NoesisInstance
        const guiInstance = NoesisViewUtils.createNoesisInstance(xamlPath, viewMode, gameInstance);
        if (!guiInstance) {
            return null;
        }

        // 阶段3：添加到视口
        if (NoesisViewUtils.attachToViewport(guiInstance, gameInstance)) {
            console.log("HomeGUI: 主菜单界面创建成功");
            return guiInstance;
        } else {
            return null;
        }
    }
}