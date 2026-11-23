// Fill out your copyright notice in the Description page of Project Settings.

#include "KDEnemyWidgetController.h"
#include "KD/AttributeSet/KDAttributeSet.h"

void UKDEnemyWidgetController::BroadcastInitialValues()
{
	UKDAttributeSet* KDSet = Cast<UKDAttributeSet>(AttributeSet);
	if (!KDSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: AttributeSet 不是 UKDAttributeSet，无法广播初始值。"), *GetName());
		return;
	}

	OnHealthChanged.Broadcast(KDSet->GetHealth());
	OnMaxHealthChanged.Broadcast(KDSet->GetMaxHealth());
}

void UKDEnemyWidgetController::BindCallbacksToDependencies()
{
	UKDAttributeSet* KDSet = Cast<UKDAttributeSet>(AttributeSet);
	if (!KDSet || !AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDSet->GetHealthAttribute())
		.AddUObject(this, &UKDEnemyWidgetController::HandleHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(KDSet->GetMaxHealthAttribute())
		.AddUObject(this, &UKDEnemyWidgetController::HandleMaxHealthChanged);
}

bool UKDEnemyWidgetController::AreParamsValid() const
{
	// 敌人挂在 Character 上，没有 PlayerController / PlayerState。
	return AbilitySystemComponent && AttributeSet;
}

void UKDEnemyWidgetController::HandleHealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UKDEnemyWidgetController::HandleMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
