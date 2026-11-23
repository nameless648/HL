// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KDWidgetController.h"
#include "KDOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKDOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKDOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKDOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKDOnMaxManaChangedSignature, float, NewMaxMana);

/**
 * Overlay（HUD 血条/蓝条）专用的 Controller。
 *
 * View 侧只需要在蓝图里绑这四个委托：初始值和之后的每次变化都从同一条路进来，
 * 所以进度条不用区分“第一次赋值”和“后来更新”。
 */
UCLASS(BlueprintType, Blueprintable)
class KD_API UKDOverlayWidgetController : public UKDWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "KD|Attributes")
	FKDOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "KD|Attributes")
	FKDOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "KD|Attributes")
	FKDOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "KD|Attributes")
	FKDOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	void HandleHealthChanged(const FOnAttributeChangeData& Data);
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data);
	void HandleManaChanged(const FOnAttributeChangeData& Data);
	void HandleMaxManaChanged(const FOnAttributeChangeData& Data);
};
