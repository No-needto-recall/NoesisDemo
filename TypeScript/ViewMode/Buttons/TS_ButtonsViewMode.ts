import * as UE from 'ue';
import { uproperty,uparam,ufunction } from 'ue';

class TS_ButtonsViewMode extends UE.Object{
    //@no-blueprint
    static Path():string{
        return "/Game/BluePrints/TypeScript/ViewMode/Buttons/TS_ButtonsViewMode.TS_ButtonsViewMode_C";
    }
    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite,uproperty.Category="TEST Category")
    TestValue:string;

    @ufunction.ufunction(ufunction.BlueprintCallable)
    StartCommand():void{
        console.log("StartCommand Clicked");
    }

    @ufunction.ufunction(ufunction.BlueprintCallable)
    SettingsCommand():void{
        console.log("SettingsCommand Clicked");
    }

    @ufunction.ufunction(ufunction.BlueprintCallable)
    ExitCommand():void{
        console.log("ExitCommand Clicked");
    }

}

export default TS_ButtonsViewMode;