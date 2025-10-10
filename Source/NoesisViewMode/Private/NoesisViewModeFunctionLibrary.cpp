#include "NoesisViewModeFunctionLibrary.h"
#include "NoesisViewModeInstance.h"
#include "NoesisInstance.h"
#include "NoesisXaml.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogBbtNoesisLibrary, Log, All);

UNoesisViewModeInstance* UNoesisViewModeFunctionLibrary::CreateNoesisInstance(
    UObject* WorldContextObject,
    UNoesisXaml* XamlAsset, 
    APlayerController* PlayerController,
    UObject* DataContext)
{
    // 参数验证
    if (!XamlAsset)
    {
        UE_LOG(LogBbtNoesisLibrary, Error, TEXT("BbtNoesisGUI: XamlAsset is null"));
        return nullptr;
    }

    if (!PlayerController)
    {
        UE_LOG(LogBbtNoesisLibrary, Error, TEXT("BbtNoesisGUI: PlayerController is null"));
        return nullptr;
    }

    // 获取 World
    UWorld* World = nullptr;
    if (WorldContextObject)
    {
        World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    }
    
    if (!World && PlayerController)
    {
        World = PlayerController->GetWorld();
    }

    if (!World)
    {
        UE_LOG(LogBbtNoesisLibrary, Error, TEXT("BbtNoesisGUI: No valid World found"));
        return nullptr;
    }

    UE_LOG(LogBbtNoesisLibrary, Log, TEXT("BbtNoesisGUI: Creating NoesisInstance for XAML '%s'"), *XamlAsset->GetName());

    // 使用自定义的 BbtNoesisInstance
    // 1. 创建实例
    UNoesisViewModeInstance* Instance = NewObject<UNoesisViewModeInstance>(World);
    if (!Instance)
    {
        UE_LOG(LogBbtNoesisLibrary, Error, TEXT("BbtNoesisGUI: Failed to create BbtNoesisInstance"));
        return nullptr;
    }

    // 2. 设置 XAML 资产（必须）
    Instance->BaseXaml = XamlAsset;
    
    // 3. 如果提供了 DataContext，设置为 PendingDataContext
    if (DataContext)
    {
        Instance->PendingDataContext = DataContext;
        UE_LOG(LogBbtNoesisLibrary, Log, TEXT("BbtNoesisGUI: DataContext set to PendingDataContext"));
    }

    // 4. 设置拥有者（重要）
    Instance->SetOwningPlayer(PlayerController);

    // 5. 初始化 - 会触发 XamlLoaded，在那里设置 DataContext
    Instance->Initialize();

    // 注意：不需要手动调用 InitInstance()
    // NoesisInstance::NativeConstruct() 会在 Widget 构建时自动调用 InitInstance()

    UE_LOG(LogBbtNoesisLibrary, Log, TEXT("BbtNoesisGUI: BbtNoesisInstance created successfully"));
    return Instance;
}
