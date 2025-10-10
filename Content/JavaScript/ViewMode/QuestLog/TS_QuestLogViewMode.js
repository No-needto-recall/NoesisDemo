"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
const UE = require("ue");
const ue_1 = require("ue");
const TS_Quest_1 = require("./TS_Quest");
const NoesisProxy_1 = require("../../NoesisProxy");
class TS_QuestLogViewMode extends UE.Object {
    //@no-blueprint
    static Path() {
        return "/Game/BluePrints/TypeScript/ViewMode/QuestLog/TS_QuestLogViewMode.TS_QuestLogViewMode_C";
    }
    AddQuest(Title, Image, Difficulty, Description, Completed) {
        const QuestClass = UE.Class.Load(TS_Quest_1.default.Path());
        let Quest = UE.NewObject(QuestClass);
        Quest.Initialize(Title, Image, Difficulty, Description, Completed);
        let Proxy = (0, NoesisProxy_1.createNoesisProxy)(this);
        Proxy.Quests.Add(Quest);
        return Quest;
    }
}
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_QuestLogViewMode.prototype, "Quests", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_QuestLogViewMode.prototype, "SelectedQuest", void 0);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], TS_QuestLogViewMode.prototype, "AddQuest", null);
exports.default = TS_QuestLogViewMode;
//# sourceMappingURL=TS_QuestLogViewMode.js.map