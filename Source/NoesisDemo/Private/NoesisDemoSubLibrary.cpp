// Fill out your copyright notice in the Description page of Project Settings.


#include "NoesisDemoSubLibrary.h"
#include "NoesisDemoPuertsSubsystem.h"
#include "Kismet/GameplayStatics.h"

UNoesisDemoPuertsSubsystem* UNoesisDemoSubLibrary::GetPuertsSub(UObject* InWorld)
{
	UGameInstance* GI = UGameplayStatics::GetGameInstance(InWorld);
	if (GI)
	{
		return GI->GetSubsystem<UNoesisDemoPuertsSubsystem>();
	}
	return nullptr;
}
