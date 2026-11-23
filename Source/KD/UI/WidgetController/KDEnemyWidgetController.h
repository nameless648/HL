// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KDWidgetController.h"
#include "KDEnemyWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKDOnEnemyHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKDOnEnemyMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 敌人头顶血条的 Controller。
 *
 * 敌人没有 PlayerController / PlayerState，所以这里只要求 ASC + AttributeSet；
 * 其余（View 注入、初始值广播、变化订阅）沿用 UKDWidgetController 的生命周期。
 */
UCLASS(BlueprintType, Blueprintable)
class KD_API UKDEnemyWidgetController : public UKDWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	virtual bool AreParamsValid() const override;

	UPROPERTY(BlueprintAssignable, Category = "KD|Attributes")
	FKDOnEnemyHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "KD|Attributes")
	FKDOnEnemyMaxHealthChangedSignature OnMaxHealthChanged;

protected:
	void HandleHealthChanged(const FOnAttributeChangeData& Data);
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data);
};
