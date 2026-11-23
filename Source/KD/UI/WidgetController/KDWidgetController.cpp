// Fill out your copyright notice in the Description page of Project Settings.

#include "KDWidgetController.h"

void UKDWidgetController::SetWidgetControllerParams(const FKDWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void UKDWidgetController::InitWidgetController()
{
	if (!AreParamsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: WidgetControllerParams 不完整，跳过初始化。"), *GetName());
		return;
	}

	// 顺序很重要：先把当前值推给 View，再订阅变化。
	// 反过来的话，绑定期间如果属性恰好变化，View 会先收到一次“变化”，再被初始值覆盖。
	BroadcastInitialValues();
	BindCallbacksToDependencies();
}

bool UKDWidgetController::AreParamsValid() const
{
	return PlayerController && PlayerState && AbilitySystemComponent && AttributeSet;
}

void UKDWidgetController::BroadcastInitialValues()
{
}

void UKDWidgetController::BindCallbacksToDependencies()
{
}
