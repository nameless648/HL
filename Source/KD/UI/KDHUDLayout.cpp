// Fill out your copyright notice in the Description page of Project Settings.

#include "KDHUDLayout.h"
#include "KD/GameplayTags/KDTags.h"
#include "KD/UI/KDMenuWidget.h"
#include "KD/UI/KDUIManagerSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UKDHUDLayout::NativeConstruct()
{
	Super::NativeConstruct();

	if (UKDUIManagerSubsystem* UIManager = UKDUIManagerSubsystem::Get(this))
	{
		UIManager->RegisterLayout(GetOwningPlayer(), this);
	}
}

void UKDHUDLayout::NativeDestruct()
{
	if (UKDUIManagerSubsystem* UIManager = UKDUIManagerSubsystem::Get(this))
	{
		UIManager->UnregisterLayout(GetOwningPlayer());
	}

	Super::NativeDestruct();
}

UCommonActivatableWidgetContainerBase* UKDHUDLayout::GetStack(FGameplayTag Layer) const
{
	if (Layer.MatchesTagExact(KDTags::UI::Layer::Game) && GameStack)
	{
		return GameStack;
	}

	if (Layer.MatchesTagExact(KDTags::UI::Layer::Modal) && ModalStack)
	{
		return ModalStack;
	}

	// 默认落到菜单层。
	return MenuStack;
}

UKDMenuWidget* UKDHUDLayout::PushMenuToLayer(TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer)
{
	UCommonActivatableWidgetContainerBase* Stack = GetStack(Layer);
	if (!Stack || !MenuClass)
	{
		return nullptr;
	}

	return Stack->AddWidget<UKDMenuWidget>(MenuClass);
}

void UKDHUDLayout::PopMenuFromLayer(FGameplayTag Layer)
{
	UCommonActivatableWidgetContainerBase* Stack = GetStack(Layer);
	if (!Stack)
	{
		return;
	}

	if (UCommonActivatableWidget* ActiveWidget = Stack->GetActiveWidget())
	{
		Stack->RemoveWidget(*ActiveWidget);
	}
}

void UKDHUDLayout::ClearLayer(FGameplayTag Layer)
{
	if (UCommonActivatableWidgetContainerBase* Stack = GetStack(Layer))
	{
		Stack->ClearWidgets();
	}
}

UKDMenuWidget* UKDHUDLayout::GetActiveMenu(FGameplayTag Layer) const
{
	UCommonActivatableWidgetContainerBase* Stack = GetStack(Layer);
	return Stack ? Cast<UKDMenuWidget>(Stack->GetActiveWidget()) : nullptr;
}

bool UKDHUDLayout::HasMenuInLayer(FGameplayTag Layer) const
{
	UCommonActivatableWidgetContainerBase* Stack = GetStack(Layer);
	return Stack && Stack->GetNumWidgets() > 0;
}

bool UKDHUDLayout::IsMenuActiveInLayer(TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer) const
{
	UCommonActivatableWidgetContainerBase* Stack = GetStack(Layer);
	if (!Stack || !MenuClass)
	{
		return false;
	}

	const UCommonActivatableWidget* ActiveWidget = Stack->GetActiveWidget();
	return ActiveWidget && ActiveWidget->IsA(MenuClass);
}
