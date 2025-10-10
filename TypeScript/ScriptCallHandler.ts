import * as UE from 'ue';
import { createNoesisProxy } from './NoesisProxy';
import { NoesisViewUtils } from './NoesisViewUtils';
import TS_NoesisViewMode from './ViewMode/TS_NoesisViewMode';
import TS_ButtonsViewMode from './ViewMode/Buttons/TS_ButtonsViewMode';
import TS_QuestLogViewMode from './ViewMode/QuestLog/TS_QuestLogViewMode';
import { QuestDifficulty } from './ViewMode/QuestLog/TS_Quest';

/**
 * 脚本调用处理器
 * 负责处理来自 C++ 的 TypeScript 脚本调用
 */
export class ScriptCallHandler {
    private readonly gameInstance: UE.NoesisDemoGameInstance;

    constructor(gameInstance: UE.NoesisDemoGameInstance) {
        this.gameInstance = gameInstance;
    }

    /**
     * 处理脚本函数调用
     */
    public CallOnFunc(funcTag: UE.GameplayTag, inContent: UE.InstancedStruct): void {
        console.log("Start CallOnFunc Name ", funcTag.TagName);
        if (funcTag.TagName === "TypeScript.HomeRun") {
            this.HomeRun();
        } else if (funcTag.TagName === "TypeScript.ButtonsDemo") {
            this.ButtonsDemo();
        } else if (funcTag.TagName === "TypeScript.QuestLogDemo") {
            this.QuestLogDemo();
        }


        console.log("End CallOnFunc");
    }

    private HomeRun() {
        // 演示三阶段创建和修改 ViewMode 的过程
        const xamlPath = "/Game/GUI/MainPage.MainPage";
        const viewModeClassPath = TS_NoesisViewMode.Path();

        // ========== 阶段1：创建 ViewMode (Constructor 被调用) ==========
        console.log("===== 阶段1:创建 ViewMode =====");
        const viewMode = NoesisViewUtils.createViewMode(viewModeClassPath);
        if (!viewMode) {
            console.error("Failed to create ViewMode");
            return;
        }

        // ========== 阶段2：创建后但未绑定到 Instance 之前修改 ==========
        console.log("===== 阶段2:ViewMode 创建后,Instance 创建前修改 =====");
        // 使用 Proxy 包装，实现自动通知
        const proxyViewMode = createNoesisProxy<TS_NoesisViewMode>(viewMode);
        if (proxyViewMode) {
            // 在绑定到 Instance 之前修改初始值
            proxyViewMode.TestValue = "Modified before binding to Instance";
            proxyViewMode.StrArr.Add("Item added before Instance");
            proxyViewMode.StrArr.Add("Another item before Instance");
        }

        // 创建 NoesisInstance（此时 ViewMode 已经被修改过）
        const guiInstance = NoesisViewUtils.createNoesisInstance(xamlPath, viewMode, this.gameInstance);
        if (!guiInstance) {
            console.error("Failed to create NoesisInstance");
            return;
        }

        // ========== 阶段3：绑定到 Instance 并添加到屏幕后继续修改 ==========
        console.log("===== 阶段3：添加到视口后继续修改 =====");
        if (NoesisViewUtils.attachToViewport(guiInstance, this.gameInstance)) {
            // 添加到屏幕后，继续修改数据
            if (proxyViewMode) {
                proxyViewMode.TestValue = "Modified after display on screen!";
                proxyViewMode.StrArr.Add("Item added after display");
                // proxyViewMode.StrMap.Add("1", "Map added after display");
                console.log("Final TestValue: ", proxyViewMode.TestValue);
            }
            console.log("HomeGUI: 主菜单界面创建成功，所有阶段完成");
        }
    }

    private ButtonsDemo(){
            const xamlPath = "/Game/GUI/Buttons/MainWindow.MainWindow";
            const viewModeClassPath = TS_ButtonsViewMode.Path();
            const viewMode = NoesisViewUtils.createViewMode(viewModeClassPath);
            if (!viewMode) {
                console.error("Failed to create ViewMode");
                return;
            }
            const guiInstance = NoesisViewUtils.createNoesisInstance(xamlPath, viewMode, this.gameInstance);
            if (!guiInstance) {
                console.error("Failed to create NoesisInstance");
                return;
            }
            if (NoesisViewUtils.attachToViewport(guiInstance, this.gameInstance)) {
                console.log("ButtonsGUI: 按钮界面创建成功，所有阶段完成");
            }
    }

    private QuestLogDemo(){
        const xamlPath = "/Game/GUI/QuestLog/MainPage.MainPage";
        const viewModeClassPath = TS_QuestLogViewMode.Path();
        const viewMode = NoesisViewUtils.createViewMode(viewModeClassPath);
        if (!viewMode) {
            console.error("Failed to create ViewMode");
            return;
        }
        const proxyViewMode = createNoesisProxy<TS_QuestLogViewMode>(viewMode);
        if (proxyViewMode) {
            const Images0 = UE.Texture2D.Load("/Game/GUI/QuestLog/Images/Image0.Image0");
            const Images1 = UE.Texture2D.Load("/Game/GUI/QuestLog/Images/Image1.Image1");
            const Images2 = UE.Texture2D.Load("/Game/GUI/QuestLog/Images/Image2.Image2");
            const Background = UE.Texture2D.Load("/Game/GUI/QuestLog/Images/Background.Background");
            proxyViewMode.AddQuest("Nature's Uprising", Images0, QuestDifficulty.Easy, 
                "“The timeless, tireless jaws of nature, which shaped our world since its inception, shall one day devour us all.”", false);
            proxyViewMode.AddQuest("Calming the Wake", Images1, QuestDifficulty.Normal, 
                "“The rangers warned us of reports of malevolent evil energy swelling and pouring out of the dark Marshes.”", true);
            proxyViewMode.AddQuest("Tomen's Curiosity", Images2, QuestDifficulty.Easy, 
                "“Back to camp from the battle, lieutenant Tomen awaits your return with the loot of last night's skirmish.”", false);
            proxyViewMode.AddQuest("Forest in Dispair", Images0, QuestDifficulty.Normal, 
                "“Wild animals are growing more and more aggressive near Eastburg, and our men suffers constant attacks from wolves!”", true);
            proxyViewMode.AddQuest("Retaliation", Images1, QuestDifficulty.Hard, 
                "“The goblins are among the most ancient and bitter rivals of the Dwarven brethen, and yet again we should clash.”", true);
            proxyViewMode.AddQuest("Living Hearts", Images2, QuestDifficulty.Easy, 
                "“Venture into the depths of this land, and old lover's curse may be a blessing in disguise near the BrokenHeart's Well.”", false);
            proxyViewMode.AddQuest("Scout their Defenses", Images0, QuestDifficulty.Easy, 
                "“Elwin believes that you can score a telling blow against the Black Ogres and their masters in the northern Amberwood.”", false);
            proxyViewMode.AddQuest("Rescue the Leader", Images1, QuestDifficulty.Hard, 
                "“Enter into their dwelling and release as many of the captives as possible. Find them quickly!”", true);
            proxyViewMode.AddQuest("Golden Oportunity", Images2, QuestDifficulty.Hard, 
                "“You restored the good name of the Purple Guard, and master Proudbeard is delighted at what you have done.”", false);
            proxyViewMode.AddQuest("Loyal Subordinates", Images2, QuestDifficulty.Easy, 
                "“You have helped us before, and if you continue to do so we will not forget it. Neither will the Orcs, to be sure.”", true);
            proxyViewMode.AddQuest("Legacy of the Past", Images1, QuestDifficulty.Normal, 
                "“Word of your deeds travelled far, and you became much sought-after by those who have need of such a champion!”", true);
            proxyViewMode.SelectedQuest = proxyViewMode.AddQuest("Purging the Dead", Images2, QuestDifficulty.Hard, 
                "“I think he said he hid it in a tall tree east of the River Falls in the Autumn Valley. Beware of the Necromancer!”", false);
        }
        const guiInstance = NoesisViewUtils.createNoesisInstance(xamlPath, viewMode, this.gameInstance);
        if (!guiInstance) {
            console.error("Failed to create NoesisInstance");
            return;
        }
        if (NoesisViewUtils.attachToViewport(guiInstance, this.gameInstance)) {
            console.log("QuestLogGUI: 任务日志界面创建成功，所有阶段完成");
        }
    }

}