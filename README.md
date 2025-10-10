# NoesisDemo - 基于 TypeScript 的 NoesisGUI 开发方案

<div align="center">

**Unreal Engine 5.4 + NoesisGUI + PuerTS**

*用 TypeScript 优雅地开发 XAML 界面*

[English](README_EN.md) | 简体中文

</div>

---

## 📖 项目简介

这是一个 **Unreal Engine 5.4** 示例项目，展示了如何使用 **TypeScript** 编写 **NoesisGUI** 的 ViewMode，实现完整的 MVVM 数据绑定。

传统的 NoesisGUI 开发方式需要在蓝图或 C++ 中编写 ViewMode，而本项目通过 **PuerTS** 的 [`uclass_extends`](https://puerts.github.io/docs/puerts/unreal/uclass_extends/) 功能，让开发者可以用 TypeScript 编写 ViewMode，享受**代码化开发**带来的诸多优势。

### 📚 相关文档

- **PuerTS UClass Extends**：[https://puerts.github.io/docs/puerts/unreal/uclass_extends/](https://puerts.github.io/docs/puerts/unreal/uclass_extends/)
- **NoesisGUI Property Change Notifications**：[https://www.noesisengine.com/docs/Gui.Core.UnrealTutorial.html#property-change-notifications](https://www.noesisengine.com/docs/Gui.Core.UnrealTutorial.html#property-change-notifications)

### ✨ 核心特性

- ✅ **完美复刻官方示例**：成功用 TypeScript 复刻了 NoesisGUI 官方的 **Buttons** 和 **QuestLog** 示例
- 🚀 **TypeScript 代码化 ViewMode**：使用 PuerTS 的 `uclass_extends` 继承 UE 类，自动生成蓝图
- 🔧 **动态 DataContext 设置**：自定义 `UNoesisViewModeInstance` 解决官方限制
- 🤖 **AI 友好**：XAML 和 ViewMode 都是代码，易于被 AI 理解和生成
- 📦 **版本控制友好**：完全代码化，告别蓝图文件的合并冲突
- ⚡ **自动属性通知**：NoesisProxy 自动处理 PropertyChanged，支持 TArray 和 TMap

---

## 🎯 为什么选择这个方案？

### 传统蓝图方案的痛点

1. **合并冲突噩梦**：蓝图文件合并冲突难以解决，团队协作困难
2. **AI 无法理解**：AI 无法读取和生成蓝图，无法享受 AI 辅助开发的便利
3. **版本控制困难**：蓝图文件是二进制格式，diff 和 code review 困难

### TypeScript 方案的优势

| 特性 | 蓝图方案 | **TypeScript 方案** |
|------|---------|---------------------|
| 合并冲突 | ❌ 难以解决 | ✅ 文本格式，易于合并 |
| AI 辅助 | ❌ AI 无法理解 | ✅ AI 完全理解，可生成代码 |
| 代码审查 | ❌ 无法 diff | ✅ 标准 Git diff |
| 类型安全 | ⚠️ 部分支持 | ✅ 完整 TypeScript 类型系统 |
| 开发效率 | ⚠️ 可视化编辑 | ✅ 代码编辑器 + 智能提示 |
| 版本控制 | ❌ 二进制文件 | ✅ 纯文本文件 |

---

## 🏗️ 技术架构

### 核心组件

```
┌─────────────────────────────────────────────────────────────┐
│                      开发流程                                 │
├─────────────────────────────────────────────────────────────┤
│  1. 设计师提供 XAML                                           │
│     Assets/GUI/Buttons/MainWindow.xaml                       │
│                                                               │
│  2. 开发者编写 TypeScript ViewMode                            │
│     TypeScript/ViewMode/Buttons/TS_ButtonsViewMode.ts        │
│                                                               │
│  3. PuerTS 自动生成蓝图类                                     │
│     /Game/BluePrints/TypeScript/ViewMode/Buttons/...         │
│                                                               │
│  4. TypeScript 创建实例并绑定                                 │
│     NoesisViewUtils.createViewMode() → NewObject()           │
│     NoesisViewUtils.createNoesisInstance()                   │
└─────────────────────────────────────────────────────────────┘
```

### 三大核心技术

#### 1. PuerTS 的 `uclass_extends` - 蓝图类生成

```typescript
// TypeScript/ViewMode/Buttons/TS_ButtonsViewMode.ts
// 查看完整代码：https://github.com/No-needto-recall/NoesisDemo/blob/main/TypeScript/ViewMode/Buttons/TS_ButtonsViewMode.ts
import * as UE from 'ue';
import { uproperty, ufunction } from 'ue';

class TS_ButtonsViewMode extends UE.Object {
    // 静态方法：返回生成的蓝图类路径
    static Path(): string {
        return "/Game/BluePrints/TypeScript/ViewMode/Buttons/TS_ButtonsViewMode.TS_ButtonsViewMode_C";
    }

    // 使用装饰器定义属性，可在 XAML 中绑定
    @uproperty.uproperty(uproperty.EditAnywhere, uproperty.BlueprintReadWrite)
    TestValue: string;

    // 使用装饰器定义命令，可在 XAML 中绑定
    @ufunction.ufunction(ufunction.BlueprintCallable)
    StartCommand(): void {
        console.log("StartCommand Clicked");
    }
}
```

**PuerTS 会自动生成对应的蓝图类**，路径为 `/Game/BluePrints/TypeScript/ViewMode/Buttons/TS_ButtonsViewMode_C`

#### 2. UNoesisViewModeInstance - 解决 DataContext 限制

官方的 `UNoesisInstance` **不允许动态设置 DataContext**，因此我们自定义了一个子类：

```cpp
// Source/NoesisViewMode/Public/NoesisViewModeInstance.h
// 查看完整代码：https://github.com/No-needto-recall/NoesisDemo/blob/main/Source/NoesisViewMode/Public/NoesisViewModeInstance.h
UCLASS()
class UNoesisViewModeInstance : public UNoesisInstance {
    GENERATED_BODY()

public:
    // 待设置的 DataContext
    UPROPERTY()
    UObject* PendingDataContext;

protected:
    // 重写 XamlLoaded 事件，在 XAML 加载完成后设置 DataContext
    virtual void XamlLoaded_Implementation() override;
};
```

**关键点**：在 `XamlLoaded` 回调中设置 DataContext，确保 XAML 加载完成后再绑定数据。

#### 3. NoesisProxy - 自动属性通知

使用 JavaScript Proxy API 拦截属性修改，自动触发 NoesisGUI 的通知：

```typescript
// NoesisProxy.ts - 查看完整代码：https://github.com/No-needto-recall/NoesisDemo/blob/main/TypeScript/NoesisProxy.ts
// 创建 ViewMode
const viewMode = NoesisViewUtils.createViewMode(TS_ButtonsViewMode.Path());

// 使用 Proxy 包装，实现自动通知
const proxy = createNoesisProxy<TS_ButtonsViewMode>(viewMode);

// 任何属性修改都会自动通知 NoesisGUI 更新
proxy.TestValue = "New Value";  // 自动调用 NotifyPropertyChanged

// 支持 TArray 自动通知
proxy.items.Add(newItem);       // 自动调用 NotifyArrayPostAdd
proxy.items.RemoveAt(0);        // 自动调用 NotifyArrayPreRemove + NotifyArrayPostRemove

// 支持 TMap 自动通知
proxy.map.Add("key", value);    // 自动调用 NotifyMapPostAdd
```

---

## 🚀 快速开始

### ⚠️ 平台支持

**当前版本仅支持 Windows 平台**
- ✅ 仓库包含预编译的 Windows Editor DLL，可直接使用
- ✅ 克隆后可直接双击 `NoesisDemo.uproject` 打开编辑器
- ⚠️ **Mac/Linux 用户**：需要自行编译 C++ 代码后才能使用

### 环境要求

- **操作系统**: Windows 10/11
- **Unreal Engine**: 5.4
- **NoesisGUI 插件**: 3.2+
- **PuerTS 插件**: 最新版
- **TypeScript**: 需要全局安装 `tsc` 命令
- **Visual Studio**（可选）：仅在需要修改 C++ 代码时必须
- **Noesis Studio**（可选）：用于 XAML 可视化设计，参见 [Noesis Studio with Unreal](https://www.noesisengine.com/forums/viewtopic.php?t=3610)

### 📦 安装步骤

**Windows 用户（推荐）**：
```bash
# 1. 克隆仓库（无需 Git LFS）
git clone https://github.com/No-needto-recall/NoesisDemo.git

# 2. 直接双击 NoesisDemo.uproject 打开项目
# ✅ 无需编译，开箱即用！
# ✅ 无需安装 Git LFS（已修复）
```

> **注意**：如果遇到"找不到插件"的错误，请确保使用最新的仓库版本（2025-10-10 之后）。早期版本存在 Git LFS 配置问题，已修复。

**Mac/Linux 用户**：
```bash
# 1. 克隆仓库
git clone https://github.com/No-needto-recall/NoesisDemo.git

# 2. 编译 C++ 代码（首次使用必须）
# 参考 Unreal Engine 官方文档进行平台编译配置

# 3. 双击 NoesisDemo.uproject 打开项目
```

### 🎨 使用 Noesis Studio 开发

本项目完全支持使用官方的 [Noesis Studio](https://www.noesisengine.com/forums/viewtopic.php?t=3610) 进行 XAML 可视化开发：

1. **实时预览**：在 Noesis Studio 中编辑 XAML，即时看到效果
2. **DataContext 绑定**：Studio 能够识别 TypeScript 生成的蓝图类作为 DataContext
3. **无缝集成**：修改后的 XAML 文件会自动同步到 UE 项目

**工作流程**：
```
设计师在 Noesis Studio 中设计 XAML
       ↓
保存到 Assets/GUI/ 目录
       ↓
UE 自动导入更新
       ↓
开发者用 TypeScript 编写 ViewMode 逻辑
```

### 编译 TypeScript

```bash
# 在项目根目录执行
tsc

# 或使用监视模式（自动编译）
tsc --watch
```

编译后的 JavaScript 文件会输出到 `Content/JavaScript` 目录。

### 创建一个简单的界面

#### 1. 创建 XAML 文件

```xaml
<!-- Assets/GUI/MyView.xaml -->
<UserControl xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
    <StackPanel>
        <TextBlock Text="{Binding Message}" FontSize="24"/>
        <Button Content="Click Me" Command="{Binding OnClick}"/>
    </StackPanel>
</UserControl>
```

#### 2. 创建 TypeScript ViewMode

```typescript
// TypeScript/ViewMode/MyViewMode.ts
import * as UE from 'ue';
import { uproperty, ufunction } from 'ue';

class MyViewMode extends UE.Object {
    static Path(): string {
        return "/Game/BluePrints/TypeScript/ViewMode/MyViewMode.MyViewMode_C";
    }

    @uproperty.uproperty(uproperty.EditAnywhere, uproperty.BlueprintReadWrite)
    Message: string = "Hello NoesisGUI!";

    @ufunction.ufunction(ufunction.BlueprintCallable)
    OnClick(): void {
        console.log("Button clicked!");
    }
}

export default MyViewMode;
```

#### 3. 在 TypeScript 中创建和显示界面

```typescript
import { NoesisViewUtils } from './NoesisViewUtils';
import { createNoesisProxy } from './NoesisProxy';
import MyViewMode from './ViewMode/MyViewMode';

// 1. 创建 ViewMode 实例
const viewMode = NoesisViewUtils.createViewMode(MyViewMode.Path());

// 2. 使用 Proxy 包装（可选，启用自动通知）
const proxy = createNoesisProxy<MyViewMode>(viewMode);
proxy.Message = "Hello from TypeScript!";

// 3. 创建 NoesisInstance
const xamlPath = "/Game/GUI/MyView.MyView";
const instance = NoesisViewUtils.createNoesisInstance(xamlPath, viewMode, gameInstance);

// 4. 添加到视口
NoesisViewUtils.attachToViewport(instance, gameInstance);
```

---

## 📂 项目结构

```
NoesisDemo/
├── Assets/                         # NoesisGUI 资源
│   └── GUI/                        # XAML 界面文件
│       ├── Buttons/                # Buttons 示例
│       │   ├── MainWindow.xaml
│       │   └── Resources.xaml
│       └── QuestLog/               # QuestLog 示例
│           ├── MainPage.xaml
│           └── Resources.xaml
│
├── TypeScript/                     # TypeScript 源代码
│   ├── main.ts                     # PuerTS 入口
│   ├── NoesisProxy.ts              # 自动属性通知 Proxy
│   ├── NoesisViewUtils.ts          # 视图创建工具类
│   ├── ScriptCallHandler.ts        # C++ 调用路由器
│   └── ViewMode/                   # ViewMode 实现
│       ├── Buttons/
│       │   └── TS_ButtonsViewMode.ts
│       └── QuestLog/
│           ├── TS_QuestLogViewMode.ts
│           └── TS_Quest.ts
│
├── Source/                         # C++ 源代码
│   ├── NoesisDemo/                 # 主游戏模块
│   │   ├── NoesisDemoGameInstance.h/cpp
│   │   └── NoesisDemoPuertsSubsystem.h/cpp
│   └── NoesisViewMode/             # ViewMode 框架模块
│       ├── NoesisViewModeInstance.h/cpp      # 自定义 Instance
│       └── NoesisNotifyHelperLibrary.h/cpp   # 属性通知 API
│
├── Content/
│   ├── JavaScript/                 # 编译后的 JS（tsc 输出）
│   ├── GUI/                        # 导入的 XAML 资源
│   └── BluePrints/
│       └── TypeScript/ViewMode/    # PuerTS 生成的蓝图类
│
└── Typing/                         # TypeScript 类型定义（PuerTS 生成）
```

---

## 🎨 示例说明

### Buttons 示例

复刻了 NoesisGUI 官方的 Buttons 示例，展示了：
- 基础属性绑定
- Command 绑定
- XAML 动画和样式

**XAML 绑定：**
```xaml
<Button Content="START" Command="{Binding StartCommand}"/>
<Button Content="SETTINGS" Command="{Binding SettingsCommand}"/>
<Button Content="EXIT" Command="{Binding ExitCommand}"/>
```

**TypeScript ViewMode：**
```typescript
@ufunction.ufunction(ufunction.BlueprintCallable)
StartCommand(): void {
    console.log("StartCommand Clicked");
}
```

### QuestLog 示例

复刻了 NoesisGUI 官方的 QuestLog 示例，展示了：
- **TArray 集合绑定**：任务列表
- **复杂数据对象**：Quest 类（标题、图片、难度、描述等）
- **动态数据操作**：AddQuest 方法，自动触发 UI 更新

**TypeScript ViewMode：**
```typescript
class TS_QuestLogViewMode extends UE.Object {
    @uproperty.uproperty(uproperty.EditAnywhere, uproperty.BlueprintReadWrite)
    Quests: UE.TArray<TS_Quest>;

    @uproperty.uproperty(uproperty.EditAnywhere, uproperty.BlueprintReadWrite)
    SelectedQuest: TS_Quest;

    @ufunction.ufunction(ufunction.BlueprintCallable)
    AddQuest(Title: string, Image: UE.Texture2D, ...): TS_Quest {
        const Quest = UE.NewObject(TS_Quest);
        Quest.Initialize(Title, Image, ...);

        // 使用 Proxy 自动触发 TArray 更新通知
        let Proxy = createNoesisProxy<TS_QuestLogViewMode>(this);
        Proxy.Quests.Add(Quest);

        return Quest;
    }
}
```

---

## 🔧 技术细节

### 数据绑定流程

```
1. TypeScript 类定义
   TS_ButtonsViewMode extends UE.Object
   使用 @uproperty、@ufunction 装饰器
   ↓
2. PuerTS 生成蓝图类
   /Game/BluePrints/TypeScript/ViewMode/Buttons/TS_ButtonsViewMode_C
   ↓
3. TypeScript 创建实例
   UE.Class.Load(classPath)
   UE.NewObject(ViewModeClass)
   ↓
4. 绑定到 NoesisInstance
   创建 UNoesisViewModeInstance
   设置 PendingDataContext = viewMode
   ↓
5. XAML 加载完成
   XamlLoaded 事件触发
   自动设置 DataContext
   ↓
6. 数据绑定生效
   XAML Binding → ViewMode 属性
   ↓
7. 属性更新
   NoesisProxy 拦截 → NotifyPropertyChanged → UI 刷新
```

### 属性通知 API

`UNoesisNotifyHelperLibrary` 提供了完整的属性通知 API：

```cpp
// 基础属性通知
NotifyPropertyChanged(Target, PropertyName);

// TArray 精细通知
NotifyArrayPostAdd(Target, ArrayPropertyName);
NotifyArrayPostInsert(Target, ArrayPropertyName, Index);
NotifyArrayPreRemove(Target, ArrayPropertyName, Index);
NotifyArrayPostRemove(Target, ArrayPropertyName, Index);

// TMap 精细通知（Key 必须是 FString）
NotifyMapPostAdd(Target, MapPropertyName, Key);
NotifyMapPreRemove(Target, MapPropertyName, Key);
NotifyMapPostRemove(Target, MapPropertyName, Key);
```

NoesisProxy 会自动调用这些 API，开发者无需手动调用。

---

## ⚠️ 技术限制与解决方案

### PuerTS 的限制

PuerTS 在使用 `uclass_extends` 时存在以下限制：

1. **无法生成 UStruct 和 UEnum**：TypeScript 类只能生成 UClass（蓝图类），无法生成结构体和枚举
2. **只能访问有反射信息的类型**：只有标记了 `USTRUCT()` 和 `UENUM()` 的类型才能在 TypeScript 中使用

### 解决方案

#### 方案 1：通过 C++ 声明结构体和枚举（推荐）

如果需要在多处使用复杂的结构体或枚举，建议在 C++ 中声明并添加反射信息：

```cpp
// C++ 代码
UENUM(BlueprintType)
enum class EQuestDifficulty : uint8 {
    Easy     UMETA(DisplayName = "Easy"),
    Normal   UMETA(DisplayName = "Normal"),
    Hard     UMETA(DisplayName = "Hard")
};

USTRUCT(BlueprintType)
struct FQuestData {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestDifficulty Difficulty;
};
```

这样在 TypeScript 中就可以直接使用：

```typescript
import * as UE from 'ue';

// 使用 C++ 定义的枚举
let difficulty: UE.EQuestDifficulty = UE.EQuestDifficulty.Hard;

// 使用 C++ 定义的结构体
let questData: UE.FQuestData = new UE.FQuestData();
questData.Title = "New Quest";
questData.Difficulty = UE.EQuestDifficulty.Easy;
```

#### 方案 2：使用 String + TypeScript 枚举映射（灵活）

如果逻辑上可以绕过结构体和枚举，可以使用 **String** 代替枚举，并在 TypeScript 中定义常量映射。这是 **QuestLog 示例**采用的方案：

```typescript
// TypeScript/ViewMode/QuestLog/TS_Quest.ts

// TypeScript 枚举，用于代码中的类型约束和智能提示
export class QuestDifficulty {
    static Easy = "Easy";
    static Normal = "Normal";
    static Hard = "Hard";
}

class TS_Quest extends UE.Object {
    // 在蓝图中是 String 类型，在 XAML 中直接显示
    @uproperty.uproperty(uproperty.EditAnywhere, uproperty.BlueprintReadWrite)
    Difficulty: string;  // 不是 enum，而是 string

    @ufunction.ufunction(ufunction.BlueprintCallable)
    Initialize(Title: string, Image: UE.Texture2D, Difficulty: string, ...): void {
        let proxy = createNoesisProxy<TS_Quest>(this);
        proxy.Difficulty = Difficulty;  // 直接赋值字符串
    }
}
```

使用时：

```typescript
// ScriptCallHandler.ts
import { QuestDifficulty } from './ViewMode/QuestLog/TS_Quest';

// 使用 TypeScript 枚举常量，获得类型提示
proxyViewMode.AddQuest("Nature's Uprising", Images0, QuestDifficulty.Easy, ...);
proxyViewMode.AddQuest("Calming the Wake", Images1, QuestDifficulty.Normal, ...);
proxyViewMode.AddQuest("Retaliation", Images2, QuestDifficulty.Hard, ...);
```

### 方案对比

| 特性 | C++ 声明 | String + TS 枚举 |
|------|---------|-----------------|
| 类型安全 | ✅ 强类型，UE 反射支持 | ⚠️ 运行时是字符串 |
| 开发效率 | ⚠️ 需要编写 C++ 代码 | ✅ 纯 TypeScript，快速迭代 |
| 跨语言使用 | ✅ C++、蓝图、TS 都能用 | ⚠️ 主要在 TS 中使用 |
| XAML 显示 | ⚠️ 需要转换器 | ✅ 直接显示字符串 |
| 适用场景 | 复杂类型，多处复用 | 简单枚举，逻辑层使用 |

**建议**：对于简单的枚举值（如难度等级），使用 String + TS 枚举方案即可；对于复杂的数据结构或需要在 C++ 和蓝图中广泛使用的类型，建议使用 C++ 声明。

---

## ⚡ 性能考量

### 性能分析

本方案**尚未进行压力测试**，但从架构角度分析，存在以下性能特点：

#### 性能开销来源

1. **跨语言调用开销**
   - TypeScript ↔ C++ 的跨语言调用存在一定开销
   - 高频调用场景下（如每帧更新的属性）可能成为瓶颈

2. **反射和静态蓝图函数调用**
   - `UNoesisNotifyHelperLibrary` 的通知函数是静态蓝图函数
   - 通过反射查找属性信息，比 C++ 直接调用 NoesisGUI 官方 API 慢

3. **NoesisProxy 拦截**
   - JavaScript Proxy 的 `set` 和 `get` 拦截会增加少量开销
   - 对于大量属性的 ViewMode，开销会累积

### 性能优化建议

#### 开发阶段：优先使用 TypeScript

```
┌─────────────────────────────────────────┐
│  开发初期（推荐使用 TypeScript）         │
├─────────────────────────────────────────┤
│  ✅ 开发效率高，快速迭代                 │
│  ✅ 代码易于修改和调试                   │
│  ✅ AI Coding 友好，自动生成代码         │
│  ✅ 版本控制友好，团队协作顺畅           │
│                                          │
│  ⚠️ 性能未优化，可能存在开销             │
└─────────────────────────────────────────┘
```

在开发初期，**强烈建议使用 TypeScript 方案**：
- 快速验证 UI 逻辑和交互
- 充分利用 AI Coding 提高开发效率
- 享受代码化带来的版本控制便利

#### 优化阶段：根据性能数据决定是否转 C++

```
┌─────────────────────────────────────────┐
│  性能优化阶段（按需转 C++）              │
├─────────────────────────────────────────┤
│  1. 进行性能分析，识别瓶颈 ViewMode      │
│  2. 对高频调用的 ViewMode 转 C++ 实现    │
│  3. 低频 ViewMode 保持 TypeScript        │
└─────────────────────────────────────────┘
```

**何时考虑转 C++**：
- ✅ ViewMode 已经稳定，不需要频繁修改
- ✅ 性能分析显示该 ViewMode 是瓶颈（高频更新属性）
- ✅ 项目进入优化阶段，追求极致性能

**转换策略**：
```cpp
// 从 TypeScript 转为 C++ ViewMode
UCLASS(Blueprintable)
class UMyViewMode : public UObject {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TestValue;

    UFUNCTION(BlueprintCallable)
    void UpdateValue(const FString& NewValue) {
        if (TestValue != NewValue) {
            TestValue = NewValue;
            // 直接调用 NoesisGUI 官方 API，性能更好
            NotifyPropertyChanged(FName("TestValue"));
        }
    }
};
```

### 性能 vs 开发效率的权衡

| 阶段 | 推荐方案 | 原因 |
|------|---------|------|
| **原型开发** | TypeScript | 快速验证想法，AI 辅助生成 |
| **功能开发** | TypeScript | 高效迭代，团队协作友好 |
| **性能优化** | 按需转 C++ | 针对瓶颈优化，保持整体效率 |
| **生产环境** | TS + C++ 混合 | 平衡开发效率和运行性能 |

**核心理念**：在开发初期享受 TypeScript 的高效率，在优化阶段针对性地转换瓶颈部分为 C++，而不是一开始就用 C++ 牺牲开发效率。

---

## 💡 开发建议

### 1. 使用 `tsc --watch` 提高效率

在开发过程中，建议开启 TypeScript 的监视模式：

```bash
tsc --watch
```

这样每次保存 TypeScript 文件时会自动编译，无需手动执行 `tsc`。

### 2. 善用 NoesisProxy

对于需要频繁更新的 ViewMode，建议使用 NoesisProxy 包装：

```typescript
const viewMode = NoesisViewUtils.createViewMode(viewModeClassPath);
const proxy = createNoesisProxy<TS_ButtonsViewMode>(viewMode);

// 后续所有修改都通过 proxy 进行
proxy.TestValue = "New Value";
```

### 3. 类型安全

TypeScript 的类型系统主要在**编写阶段**提供帮助：

```typescript
// PuerTS 通过装饰器生成蓝图，蓝图的反射信息供 NoesisGUI 使用
class TS_ButtonsViewMode extends UE.Object {
    // @uproperty 装饰器会生成蓝图属性，具有反射信息
    @uproperty.uproperty(uproperty.EditAnywhere, uproperty.BlueprintReadWrite)
    TestValue: string;  // TypeScript 类型检查在这里生效

    // @ufunction 装饰器会生成蓝图函数
    @ufunction.ufunction(ufunction.BlueprintCallable)
    StartCommand(): void {
        // 编写代码时享受 TypeScript 的类型提示和检查
    }
}
```

**注意**：TypeScript 的接口（interface）和类型别名仅在 TS 内部有效，不会生成到蓝图中。只有通过 `@uproperty` 和 `@ufunction` 装饰的成员才会被 PuerTS 生成为蓝图的反射信息。

### 4. 代码复用

将常用逻辑封装成工具函数：

```typescript
// NoesisViewUtils.ts
export class NoesisViewUtils {
    public static createViewMode(classPath: string): UE.Object | null {
        const ViewModeClass = UE.Class.Load(classPath);
        return ViewModeClass ? UE.NewObject(ViewModeClass) : null;
    }

    // ... 更多工具方法
}
```

---

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

如果你在使用过程中遇到问题，或者有任何建议，请在 [GitHub Issues](https://github.com/No-needto-recall/NoesisDemo/issues) 中告诉我们。

---

## 📄 许可证

本项目采用 MIT 许可证。

---

## 🙏 鸣谢

- [NoesisGUI](https://www.noesisengine.com/) - 强大的 XAML UI 框架
- [PuerTS](https://github.com/Tencent/puerts) - 优秀的 TypeScript 运行时
- [Unreal Engine](https://www.unrealengine.com/) - 世界领先的游戏引擎

---

## 📞 联系方式

如果你有任何问题或建议，欢迎通过以下方式联系：

- NoesisGUI 官方论坛：[https://forums.noesisengine.com/](https://forums.noesisengine.com/)
- GitHub Issues：[https://github.com/No-needto-recall/NoesisDemo/issues](https://github.com/No-needto-recall/NoesisDemo/issues)

---

<div align="center">

**用 TypeScript 开发 NoesisGUI，享受代码化带来的愉悦！**

Made with ❤️ by NoesisGUI Community

</div>
