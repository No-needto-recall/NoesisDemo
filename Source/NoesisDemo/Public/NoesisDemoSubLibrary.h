// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NoesisDemoSubLibrary.generated.h"

class UNoesisDemoPuertsSubsystem;
/**
 * 
 */
UCLASS()
class NOESISDEMO_API UNoesisDemoSubLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="NoesisDemo")
	static UNoesisDemoPuertsSubsystem* GetPuertsSub(UObject* InWorld);
};
