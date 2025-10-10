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
class TS_NoesisInstance extends UE.NoesisInstance {
}
__decorate([
    ue_1.uproperty.uproperty(ue_1.uproperty.BlueprintReadWrite, ue_1.uproperty.Category = "TEST Category")
], TS_NoesisInstance.prototype, "TestValue", void 0);
exports.default = TS_NoesisInstance;
//# sourceMappingURL=TS_NoesisInstance.js.map