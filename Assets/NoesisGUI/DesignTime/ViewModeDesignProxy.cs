using System.Collections.Generic;
using System.Windows.Input;

namespace NoesisGUI.DesignTime
{
    /// <summary>
    /// 设计时字符串 ViewMode 代理类
    /// 对应 C++ 中的 UBbt_ViewModeString
    /// </summary>
    public class DesignViewModeString
    {
        public string Value { get; set; } = "示例字符串";

        // 设置字符串值
        public ICommand Set { get; } = new RelayCommand(param => { });

        // 追加字符串到末尾
        public ICommand Append { get; } = new RelayCommand(param => { });

        // 在开头添加字符串
        public ICommand Prepend { get; } = new RelayCommand(param => { });

        // 清空字符串
        public ICommand Clear { get; } = new RelayCommand(() => { });

        // 转换为大写
        public ICommand Upper { get; } = new RelayCommand(() => { });

        // 转换为小写
        public ICommand Lower { get; } = new RelayCommand(() => { });
    }

    /// <summary>
    /// 设计时整数 ViewMode 代理类
    /// 对应 C++ 中的 UBbt_ViewModeInt32
    /// </summary>
    public class DesignViewModeInt32
    {
        public int Value { get; set; } = 100;

        // 设置整数值
        public ICommand Set { get; } = new RelayCommand(param => { });

        // 加法运算
        public ICommand Add { get; } = new RelayCommand(param => { });

        // 减法运算
        public ICommand Sub { get; } = new RelayCommand(param => { });

        // 乘法运算
        public ICommand Mul { get; } = new RelayCommand(param => { });

        // 除法运算（自动处理除零）
        public ICommand Div { get; } = new RelayCommand(param => { });

        // 自增1
        public ICommand Inc { get; } = new RelayCommand(() => { });

        // 自减1
        public ICommand Dec { get; } = new RelayCommand(() => { });

        // 重置为0
        public ICommand Reset { get; } = new RelayCommand(() => { });
    }

    /// <summary>
    /// 设计时浮点数 ViewMode 代理类
    /// 对应 C++ 中的 UBbt_ViewModeFloat
    /// </summary>
    public class DesignViewModeFloat
    {
        public float Value { get; set; } = 3.14f;

        // 设置浮点数值
        public ICommand Set { get; } = new RelayCommand(param => { });

        // 加法运算
        public ICommand Add { get; } = new RelayCommand(param => { });

        // 减法运算
        public ICommand Sub { get; } = new RelayCommand(param => { });

        // 乘法运算
        public ICommand Mul { get; } = new RelayCommand(param => { });

        // 除法运算（自动处理除零）
        public ICommand Div { get; } = new RelayCommand(param => { });

        // 自增1.0
        public ICommand Inc { get; } = new RelayCommand(() => { });

        // 自减1.0
        public ICommand Dec { get; } = new RelayCommand(() => { });

        // 重置为0.0
        public ICommand Reset { get; } = new RelayCommand(() => { });
    }

    /// <summary>
    /// 设计时事件 ViewMode 代理类
    /// 对应 C++ 中的 UBbt_ViewModeEvent
    /// </summary>
    public class DesignViewModeEvent
    {
        // 通知 NoesisGUI 执行任务
        public ICommand NotifyNoesisDoTask { get; } = new RelayCommand(() => { });
    }

    /// <summary>
    /// 设计时基础 ViewMode 代理类
    /// 对应 C++ 中的 UBbt_BaseViewMode
    /// </summary>
    public class DesignBaseViewMode
    {
        public Dictionary<string, DesignViewModeString> StringMap { get; set; } = new Dictionary<string, DesignViewModeString>
        {
            { "PlayerName", new DesignViewModeString { Value = "玩家名称" } },
            { "GameTitle", new DesignViewModeString { Value = "游戏标题" } },
            { "Status", new DesignViewModeString { Value = "状态信息" } }
        };

        public Dictionary<string, DesignViewModeInt32> Int32Map { get; set; } = new Dictionary<string, DesignViewModeInt32>
        {
            { "Money", new DesignViewModeInt32 { Value = 1000 } },
            { "Score", new DesignViewModeInt32 { Value = 2500 } },
            { "Health", new DesignViewModeInt32 { Value = 100 } },
            { "Level", new DesignViewModeInt32 { Value = 5 } }
        };

        public Dictionary<string, DesignViewModeFloat> FloatMap { get; set; } = new Dictionary<string, DesignViewModeFloat>
        {
            { "Speed", new DesignViewModeFloat { Value = 10.5f } },
            { "Damage", new DesignViewModeFloat { Value = 25.0f } },
            { "CritRate", new DesignViewModeFloat { Value = 0.15f } }
        };

        public Dictionary<string, DesignViewModeEvent> EventMap { get; set; } = new Dictionary<string, DesignViewModeEvent>
        {
            { "StartGame", new DesignViewModeEvent() },
            { "PauseGame", new DesignViewModeEvent() },
            { "SaveGame", new DesignViewModeEvent() }
        };

        // 条件管理器（设计时使用空实现）
        public object ConditionManager { get; set; }

        // 子 ViewMode 集合（延迟初始化，防止栈溢出）
        private Dictionary<string, DesignBaseViewMode> _subViewModes;
        public Dictionary<string, DesignBaseViewMode> SubViewModes 
        { 
            get 
            { 
                // 延迟初始化，只有在访问时才创建
                if (_subViewModes == null)
                {
                    _subViewModes = CreateSubViewModes();
                }
                return _subViewModes;
            }
            set { _subViewModes = value; }
        }

        private static Dictionary<string, DesignBaseViewMode> CreateSubViewModes()
        {
            // 创建简化的子 ViewMode（不包含嵌套的 SubViewModes）
            var playerVM = new DesignSubViewMode();
            playerVM.StringMap["PlayerName"] = new DesignViewModeString { Value = "玩家名称 [Player]" };

            var economyVM = new DesignSubViewMode();
            economyVM.Int32Map["Money"] = new DesignViewModeInt32 { Value = 1000 };
            economyVM.Int32Map["Score"] = new DesignViewModeInt32 { Value = 2500 };

            var battleVM = new DesignSubViewMode();
            battleVM.FloatMap["Speed"] = new DesignViewModeFloat { Value = 15.75f };
            battleVM.FloatMap["Damage"] = new DesignViewModeFloat { Value = 85.5f };

            return new Dictionary<string, DesignBaseViewMode>
            {
                { "Player", playerVM },
                { "Economy", economyVM },
                { "Battle", battleVM }
            };
        }
    }

    /// <summary>
    /// 简化的子 ViewMode 类，不包含 SubViewModes 以避免递归
    /// </summary>
    public class DesignSubViewMode : DesignBaseViewMode
    {
        public new Dictionary<string, DesignBaseViewMode> SubViewModes 
        { 
            get { return new Dictionary<string, DesignBaseViewMode>(); } 
            set { } // 忽略设置，防止递归
        }
    }
}