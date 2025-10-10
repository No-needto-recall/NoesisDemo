"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.QuestDifficulty = void 0;
const UE = require("ue");
const ue_1 = require("ue");
const NoesisProxy_1 = require("../../NoesisProxy");
class QuestDifficulty {
    static { this.Easy = "Easy"; }
    static { this.Normal = "Normal"; }
    static { this.Hard = "Hard"; }
}
exports.QuestDifficulty = QuestDifficulty;
class TS_Quest extends UE.Object {
    //@no-blueprint
    static Path() {
        return "/Game/BluePrints/TypeScript/ViewMode/QuestLog/TS_Quest.TS_Quest_C";
    }
    Initialize(Title, Image, Difficulty, Description, Completed) {
        let proxy = (0, NoesisProxy_1.createNoesisProxy)(this);
        proxy.Title = Title;
        proxy.Image = Image;
        proxy.Difficulty = Difficulty;
        proxy.Description = Description;
        proxy.Completed = Completed;
    }
}
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_Quest.prototype, "Title", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_Quest.prototype, "Image", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_Quest.prototype, "Difficulty", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_Quest.prototype, "Description", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_Quest.prototype, "Completed", void 0);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], TS_Quest.prototype, "Initialize", null);
exports.default = TS_Quest;
//# sourceMappingURL=TS_Quest.js.map