import * as UE from 'ue';
import { uproperty,uparam,ufunction } from 'ue';
import { createNoesisProxy } from '../../NoesisProxy';

export class QuestDifficulty{
    static Easy = "Easy";
    static Normal = "Normal";
    static Hard = "Hard";
}

class TS_Quest extends UE.Object{
    //@no-blueprint
    static Path():string{
        return "/Game/BluePrints/TypeScript/ViewMode/QuestLog/TS_Quest.TS_Quest_C";
    }


    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    Title:string;

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    Image:UE.Texture2D;

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    Difficulty:string;

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    Description:string;

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    Completed:boolean;

    @ufunction.ufunction(ufunction.BlueprintCallable)
    Initialize(Title:string,Image:UE.Texture2D,Difficulty:string,Description:string,Completed:boolean):void{
        let proxy = createNoesisProxy<TS_Quest>(this);
        proxy.Title = Title;
        proxy.Image = Image;
        proxy.Difficulty = Difficulty;
        proxy.Description = Description;
        proxy.Completed = Completed;
    }
}

export default TS_Quest;