// Fill out your copyright notice in the Description page of Project Settings.


#include "NoesisDemo/Public/NoesisDemoPuertsSubsystem.h"
#include "GameplayTagContainer.h"

void UNoesisDemoPuertsSubsystem::CallTypeScript(const FGameplayTag FuncTag, const FInstancedStruct& InContent)
{
	if (OnCallTypeScript.IsBound())
	{
		OnCallTypeScript.Execute(FuncTag, InContent);
	}
}

void UNoesisDemoPuertsSubsystem::CallTypeScriptWithOutContent(const FGameplayTag FuncTag)
{
	CallTypeScript(FuncTag, FInstancedStruct());
}
