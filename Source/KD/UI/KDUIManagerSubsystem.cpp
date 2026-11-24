// Fill out your copyright notice in the Description page of Project Settings.

#include "KDUIManagerSubsystem.h"
#include "KD/UI/KDHUDLayout.h"
#include "KD/UI/KDMenuWidget.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

UKDUIManagerSubsystem* UKDUIManagerSubsystem::Get(const UObject* WorldContextObject)
{
	const UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
	const UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	return GameInstance ? GameInstance->GetSubsystem<UKDUIManagerSubsystem>() : nullptr;
}

void UKDUIManagerSubsystem::RegisterLayout(APlayerController* PC, UKDHUDLayout* Layout)
{
	if (PC && Layout)
	{
		Layouts.Add(PC, Layout);
	}
}

void UKDUIManagerSubsystem::UnregisterLayout(APlayerController* PC)
{
	if (PC)
	{
		Layouts.Remove(PC);
	}
}

UKDHUDLayout* UKDUIManagerSubsystem::FindLayout(APlayerController* PC) const
{
	if (!PC)
	{
		return nullptr;
	}

	const TWeakObjectPtr<UKDHUDLayout>* Found = Layouts.Find(PC);
	return Found ? Found->Get() : nullptr;
}

UKDMenuWidget* UKDUIManagerSubsystem::PushMenu(APlayerController* PC, TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer)
{
	UKDHUDLayout* Layout = FindLayout(PC);
	if (!Layout || !MenuClass)
	{
		return nullptr;
	}

	return Layout->PushMenuToLayer(MenuClass, Layer);
}

void UKDUIManagerSubsystem::PopMenu(APlayerController* PC, FGameplayTag Layer)
{
	if (UKDHUDLayout* Layout = FindLayout(PC))
	{
		Layout->PopMenuFromLayer(Layer);
	}
}

bool UKDUIManagerSubsystem::ToggleMenu(APlayerController* PC, TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer)
{
	UKDHUDLayout* Layout = FindLayout(PC);
	if (!Layout || !MenuClass)
	{
		return false;
	}

	// 当前层就是这一类菜单：关掉。
	if (Layout->IsMenuActiveInLayer(MenuClass, Layer))
	{
		Layout->PopMenuFromLayer(Layer);
		return false;
	}

	// 这一层开着别的菜单：先清掉，再打开目标菜单。
	Layout->ClearLayer(Layer);
	Layout->PushMenuToLayer(MenuClass, Layer);
	return true;
}

bool UKDUIManagerSubsystem::HasMenu(APlayerController* PC, FGameplayTag Layer) const
{
	const UKDHUDLayout* Layout = FindLayout(PC);
	return Layout && Layout->HasMenuInLayer(Layer);
}
