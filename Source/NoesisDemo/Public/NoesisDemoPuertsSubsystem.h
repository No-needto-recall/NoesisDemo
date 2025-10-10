// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NoesisDemoPuertsSubsystem.generated.h"

struct FGameplayTag;
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnCallTypeScript, const FGameplayTag&, FuncTag, const FInstancedStruct&, InContent);
/**
 * 
 */
UCLASS()
class NOESISDEMO_API UNoesisDemoPuertsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="NoesisDemo|TypeScript")
	void CallTypeScript(const FGameplayTag FuncTag,const FInstancedStruct& InContent);

	UFUNCTION(BlueprintCallable, Category = "NoesisDemo|TypeScript")
	void CallTypeScriptWithOutContent(const FGameplayTag FuncTag);
	
	UPROPERTY()
	FOnCallTypeScript	OnCallTypeScript;
};

