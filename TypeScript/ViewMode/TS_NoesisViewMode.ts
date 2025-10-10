import * as UE from 'ue';
import { uproperty,uparam,ufunction } from 'ue';

class TS_NoesisViewMode extends UE.Object{
    //@no-blueprint
    static Path():string{
        return "/Game/BluePrints/TypeScript/ViewMode/TS_NoesisViewMode.TS_NoesisViewMode_C";
    }

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    TestValue:string = "Default Value";

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    StrArr:UE.TArray<string>;

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    StrMap:UE.TMap<string,string>;

    @ufunction.ufunction(ufunction.BlueprintCallable)
    TestFunc(param:string):void{
        console.log("TestFunc Param:",param);
        this.TestValue = param;
    }

    Constructor(){
        this.TestValue = "Default Value From Constructor";
        this.StrMap = UE.NewMap(UE.BuiltinString,UE.BuiltinString);
        this.StrMap.Add("1","Map From Constructor");
    }
}

export default TS_NoesisViewMode;