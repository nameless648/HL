// Fill out your copyright notice in the Description page of Project Settings.

#include "KDOverlayWidgetController.h"
#include "KD/AttributeSet/KDAttributeSet.h"

void UKDOverlayWidgetController::BroadcastInitialValues()
{
	UKDAttributeSet* KDSet = Cast<UKDAttributeSet>(AttributeSet);
	if (!KDSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: AttributeSet 不是 UKDAttributeSet，无法广播初始值。"), *GetName());
		return;
	}

	OnHealthChanged.Broadcast(KDSet->GetHealth());
	OnMaxHealthChanged.Broadcast(KDSet->GetMaxHealth());
	OnManaChanged.Broadcast(KDSet->GetMana());
	OnMaxManaChanged.Broadcast(KDSet->GetMaxMana());
}

void UKDOverlayWidgetController::BindCallbacksToDependencies()
{
	UKDAttributeSet* KDSet = Cast<UKDAttributeSet>(AttributeSet);
	if (!KDSet || !AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDSet->GetHealthAttribute())
		.AddUObject(this, &UKDOverlayWidgetController::HandleHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDSet->GetMaxHealthAttribute())
		.AddUObject(this, &UKDOverlayWidgetController::HandleMaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDSet->GetManaAttribute())
		.AddUObject(this, &UKDOverlayWidgetController::HandleManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDSet->GetMaxManaAttribute())
		.AddUObject(this, &UKDOverlayWidgetController::HandleMaxManaChanged);
}

void UKDOverlayWidgetController::HandleHealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UKDOverlayWidgetController::HandleMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UKDOverlayWidgetController::HandleManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UKDOverlayWidgetController::HandleMaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
