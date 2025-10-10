// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoesisInstance.h"
#include "NoesisViewModeInstance.generated.h"

class UNoesisViewModeNode;
/**
 * 自定义 NoesisInstance 子类
 * 用于在正确的时机设置 DataContext
 */
UCLASS()
class NOESISVIEWMODE_API UNoesisViewModeInstance : public UNoesisInstance
{
	GENERATED_BODY()
	
public:
	/**
	 * 待设置的 DataContext
	 * 在 XamlLoaded 事件中会自动设置
	 */
	UPROPERTY()
	UObject* PendingDataContext;
protected:
	/**
	 * 重写 XamlLoaded 事件
	 * 在 XAML 加载完成后设置 DataContext
	 */
	virtual void XamlLoaded_Implementation() override;
};