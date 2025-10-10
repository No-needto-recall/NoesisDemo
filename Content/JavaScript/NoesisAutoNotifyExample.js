"use strict";
/**
 * NoesisGUI 自动通知系统使用示例
 *
 * 这个文件展示了如何使用新的装饰器系统来实现自动属性通知
 */
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.createExampleViewModel = createExampleViewModel;
exports.createExampleViewModelWithData = createExampleViewModelWithData;
exports.demonstrateAutoNotify = demonstrateAutoNotify;
const ue_1 = require("ue");
const NoesisDecorators_1 = require("./NoesisDecorators");
const NoesisViewModelFactory_1 = require("./NoesisViewModelFactory");
// ========================================
// 示例1: 基础用法
// ========================================
class ExampleViewModel extends NoesisDecorators_1.NoesisViewModel {
    constructor() {
        super(...arguments);
        // ✅ 需要自动通知的属性：添加 @noesisNotify()
        this.PlayerName = "Player1";
        this.PlayerScore = 0;
        this.IsGameActive = false;
        // ❌ 普通属性：不需要通知的属性保持原样
        this.DebugInfo = "Debug";
    }
    StartGame() {
        console.log("Game starting...");
        // ✅ 直接赋值，自动通知！
        this.PlayerName = "Active Player";
        this.PlayerScore = 0;
        this.IsGameActive = true;
        console.log("Game started!");
    }
    AddScore(points) {
        // ✅ 自动通知
        this.PlayerScore += points;
        console.log(`Score updated: ${this.PlayerScore}`);
    }
    EndGame() {
        // ✅ 自动通知
        this.IsGameActive = false;
        console.log("Game ended!");
    }
}
__decorate([
    (0, NoesisDecorators_1.noesisNotify)(),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], ExampleViewModel.prototype, "PlayerName", void 0);
__decorate([
    (0, NoesisDecorators_1.noesisNotify)(),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], ExampleViewModel.prototype, "PlayerScore", void 0);
__decorate([
    (0, NoesisDecorators_1.noesisNotify)(),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], ExampleViewModel.prototype, "IsGameActive", void 0);
__decorate([
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere)
], ExampleViewModel.prototype, "DebugInfo", void 0);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], ExampleViewModel.prototype, "StartGame", null);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], ExampleViewModel.prototype, "AddScore", null);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], ExampleViewModel.prototype, "EndGame", null);
// ========================================
// 示例2: 复杂数据类型
// ========================================
USTRUCT();
class FPlayerStats {
    constructor() {
        this.Health = 100;
        this.Mana = 50;
        this.Level = 1;
    }
}
__decorate([
    ue_1.uproperty.uproperty()
], FPlayerStats.prototype, "Health", void 0);
__decorate([
    ue_1.uproperty.uproperty()
], FPlayerStats.prototype, "Mana", void 0);
__decorate([
    ue_1.uproperty.uproperty()
], FPlayerStats.prototype, "Level", void 0);
class AdvancedViewModel extends NoesisDecorators_1.NoesisViewModel {
    constructor() {
        super(...arguments);
        this.CurrentPlayer = "Unknown";
        // 注意：复杂对象的属性变更需要手动通知整个对象
        this.PlayerStats = new FPlayerStats();
    }
    UpdatePlayerStats(health, mana, level) {
        // 修改复杂对象的属性
        this.PlayerStats.Health = health;
        this.PlayerStats.Mana = mana;
        this.PlayerStats.Level = level;
        // ⚠️ 复杂对象需要重新赋值整个对象才能触发通知
        // 或者使用手动通知
        this.NotifyPropertyChanged("PlayerStats");
        // 或者重新赋值整个对象（推荐）
        // this.PlayerStats = Object.assign(new FPlayerStats(), this.PlayerStats);
    }
}
__decorate([
    (0, NoesisDecorators_1.noesisNotify)(),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], AdvancedViewModel.prototype, "CurrentPlayer", void 0);
__decorate([
    (0, NoesisDecorators_1.noesisNotify)(),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], AdvancedViewModel.prototype, "PlayerStats", void 0);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], AdvancedViewModel.prototype, "UpdatePlayerStats", null);
// ========================================
// 使用示例
// ========================================
/**
 * 创建 ViewModel 的推荐方式
 */
function createExampleViewModel() {
    // 方式1: 使用工厂函数
    return (0, NoesisViewModelFactory_1.createViewModel)("/Game/BluePrints/TypeScript/ExampleViewModel_C");
}
/**
 * 创建带初始属性的 ViewModel
 */
function createExampleViewModelWithData() {
    return (0, NoesisViewModelFactory_1.createViewModelWithProperties)("/Game/BluePrints/TypeScript/ExampleViewModel_C", {
        PlayerName: "Initial Player",
        PlayerScore: 1000,
        IsGameActive: true
    });
}
/**
 * 完整的使用示例
 */
function demonstrateAutoNotify() {
    console.log("=== NoesisGUI Auto-Notify Demo ===");
    // 1. 创建 ViewModel
    const viewModel = createExampleViewModel();
    // 2. 测试自动通知
    console.log("Testing auto-notify...");
    // ✅ 这些赋值都会自动触发 NoesisGUI 更新
    viewModel.PlayerName = "Demo Player";
    viewModel.PlayerScore = 500;
    viewModel.IsGameActive = true;
    // 3. 测试方法调用中的自动通知
    viewModel.StartGame();
    viewModel.AddScore(100);
    viewModel.AddScore(200);
    viewModel.EndGame();
    // 4. 验证自动通知状态
    console.log("Auto-notify enabled properties:");
    console.log("PlayerName:", viewModel.IsAutoNotifyEnabled("PlayerName"));
    console.log("PlayerScore:", viewModel.IsAutoNotifyEnabled("PlayerScore"));
    console.log("IsGameActive:", viewModel.IsAutoNotifyEnabled("IsGameActive"));
    console.log("DebugInfo:", viewModel.IsAutoNotifyEnabled("DebugInfo")); // false
    console.log("=== Demo Complete ===");
}
// ========================================
// 最佳实践总结
// ========================================
/**
 * 📝 最佳实践:
 *
 * 1. ✅ 继承 NoesisViewModel 而不是 UE.Object
 * 2. ✅ 在需要自动通知的属性上添加 @noesisNotify()
 * 3. ✅ 使用 createViewModel() 创建实例
 * 4. ✅ 直接赋值 this.Property = value，自动通知
 * 5. ⚠️ 复杂对象的嵌套属性变更需要手动通知或重新赋值整个对象
 * 6. ⚠️ 数组操作建议使用 UE.NoesisNotifyHelperLibrary 的精细通知方法
 *
 * 💡 性能提示:
 * - 只在真正需要通知 UI 的属性上使用 @noesisNotify()
 * - 频繁变化的内部计算属性不需要自动通知
 * - 对于数组/Map 的复杂操作，使用 NoesisNotifyHelperLibrary 的精细通知更高效
 */
//# sourceMappingURL=NoesisAutoNotifyExample.js.map