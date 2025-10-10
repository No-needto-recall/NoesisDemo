// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsEnv.h"
#include "Engine/GameInstance.h"
#include "NoesisDemoGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameInstanceShutdown);

/**
 * 
 */
UCLASS()
class NOESISDEMO_API UNoesisDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

protected:
	void InitPuerts();
	void ShutdownPuerts();

	UPROPERTY(BlueprintAssignable, Category="NoesisDemo|GameInstance")
	FOnGameInstanceShutdown OnGameInstanceShutdown;

	TSharedPtr<puerts::FJsEnv> JsEnv;
};
