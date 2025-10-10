#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "NoesisViewModeFunctionLibrary.generated.h"

class UNoesisViewModeInstance;
class UNoesisXaml;
class UNoesisInstance;
class UNoesisViewModeSub;
class UNoesisViewModeNode;

/**
 * NoesisGUI 静态函数库
 * 提供简化的 NoesisInstance 创建功能和子系统访问
 */
UCLASS()
class NOESISVIEWMODE_API UNoesisViewModeFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // === 基础创建函数 ===
    
    /**
     * 创建 NoesisInstance
     * @param WorldContextObject - 世界上下文
     * @param XamlAsset - XAML 资源
     * @param PlayerController - 玩家控制器
     * @param DataContext - 数据上下文（可选）
     * @return 创建的 NoesisInstance，失败返回 nullptr
     * 
     * 注意：InitInstance() 会在 NativeConstruct 中自动调用
     */
    UFUNCTION(BlueprintCallable, Category = "BbtNoesisGUI", meta = (WorldContext = "WorldContextObject"))
    static UNoesisViewModeInstance* CreateNoesisInstance(
        UObject* WorldContextObject,
        UNoesisXaml* XamlAsset, 
        APlayerController* PlayerController,
        UObject* DataContext = nullptr
    );
};