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
class TS_NoesisViewMode extends UE.Object {
    constructor() {
        super(...arguments);
        this.TestValue = "Default Value";
    }
    //@no-blueprint
    static Path() {
        return "/Game/BluePrints/TypeScript/ViewMode/TS_NoesisViewMode.TS_NoesisViewMode_C";
    }
    TestFunc(param) {
        console.log("TestFunc Param:", param);
        this.TestValue = param;
    }
    Constructor() {
        this.TestValue = "Default Value From Constructor";
        this.StrMap = UE.NewMap(UE.BuiltinString, UE.BuiltinString);
        this.StrMap.Add("1", "Map From Constructor");
    }
}
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_NoesisViewMode.prototype, "TestValue", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_NoesisViewMode.prototype, "StrArr", void 0);
__decorate([
    ue_1.uproperty.umeta(ue_1.uproperty.ExposeOnSpawn),
    ue_1.uproperty.uproperty(ue_1.uproperty.EditAnywhere, ue_1.uproperty.BlueprintReadWrite)
], TS_NoesisViewMode.prototype, "StrMap", void 0);
__decorate([
    ue_1.ufunction.ufunction(ue_1.ufunction.BlueprintCallable)
], TS_NoesisViewMode.prototype, "TestFunc", null);
exports.default = TS_NoesisViewMode;
//# sourceMappingURL=TS_NoesisViewMode.js.map