// Fill out your copyright notice in the Description page of Project Settings.


#include "NoesisDemo/Public/NoesisDemoGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogBbtGameInstance, Log, All);

void UNoesisDemoGameInstance::Init()
{
	Super::Init();
	InitPuerts();
}

void UNoesisDemoGameInstance::Shutdown()
{
	Super::Shutdown();
	ShutdownPuerts();
}

void UNoesisDemoGameInstance::InitPuerts()
{
#if WITH_EDITOR
	JsEnv = MakeShared<puerts::FJsEnv>(
		std::make_unique<puerts::DefaultJSModuleLoader>(TEXT("JavaScript")),
		std::make_shared<puerts::FDefaultLogger>(),
		9229
		);
	JsEnv->WaitDebugger(1);
#else
	// 打包版本也需要指定JavaScript模块加载器路径
	JsEnv = MakeShared<puerts::FJsEnv>(
		std::make_unique<puerts::DefaultJSModuleLoader>(TEXT("JavaScript")),
		std::make_shared<puerts::FDefaultLogger>(),
		-1  // 打包版本不启用调试端口
		);
#endif

	TArray<TPair<FString,UObject*>> Arguments;
	Arguments.Add(TPair<FString,UObject*>(TEXT("GameInstance"),this));
	if (JsEnv)
	{
		JsEnv->Start("main", Arguments);
	}else
	{
		UE_LOG(LogBbtGameInstance, Error, TEXT("Failed to Init Js Env"));
	}
}
void UNoesisDemoGameInstance::ShutdownPuerts()
{
	if (JsEnv)
	{
		if (OnGameInstanceShutdown.IsBound())
		{
			OnGameInstanceShutdown.Broadcast();
		}
	}
	JsEnv.Reset();
}
