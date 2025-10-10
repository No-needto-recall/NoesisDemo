// Fill out your copyright notice in the Description page of Project Settings.

#include "NoesisViewModeInstance.h"
#include "Engine/Engine.h"

void UNoesisViewModeInstance::XamlLoaded_Implementation()
{
	// 调用父类实现
	// 如果有待设置的 DataContext，在这里设置
	if (PendingDataContext)
	{
		UE_LOG(LogTemp, Log, TEXT("BbtNoesisInstance: Setting PendingDataContext in XamlLoaded"));
		SetDataContext(PendingDataContext);
	}
}
