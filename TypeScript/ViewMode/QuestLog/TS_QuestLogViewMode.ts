import * as UE from 'ue';
import { uproperty,uparam,ufunction } from 'ue';
import TS_Quest from './TS_Quest';
import { createNoesisProxy } from '../../NoesisProxy';

class TS_QuestLogViewMode extends UE.Object{
    //@no-blueprint
    static Path():string{
        return "/Game/BluePrints/TypeScript/ViewMode/QuestLog/TS_QuestLogViewMode.TS_QuestLogViewMode_C";
    }
    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    Quests:UE.TArray<TS_Quest>;

    @uproperty.umeta(uproperty.ExposeOnSpawn)
    @uproperty.uproperty(uproperty.EditAnywhere,uproperty.BlueprintReadWrite)
    SelectedQuest:TS_Quest;

    @ufunction.ufunction(ufunction.BlueprintCallable)
    AddQuest(Title:string,Image:UE.Texture2D,Difficulty:string,Description:string,Completed:boolean):TS_Quest{
        const QuestClass = UE.Class.Load(TS_Quest.Path());
        let Quest = UE.NewObject(QuestClass) as TS_Quest;
        Quest.Initialize(Title,Image,Difficulty,Description,Completed);
        let Proxy = createNoesisProxy<TS_QuestLogViewMode>(this);
        Proxy.Quests.Add(Quest);
        return Quest;
    }
}

export default TS_QuestLogViewMode;