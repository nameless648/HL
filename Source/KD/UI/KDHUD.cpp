// Fill out your copyright notice in the Description page of Project Settings.

#include "KDHUD.h"
#include "Widget/KDUserWidget.h"
#include "WidgetController/KDWidgetController.h"
#include "WidgetController/KDOverlayWidgetController.h"

UKDOverlayWidgetController* AKDHUD::GetOverlayWidgetController(const FKDWidgetControllerParams& WidgetControllerParams)
{
	if (!OverlayWidgetController)
	{
		if (!OverlayWidgetControllerClass)
		{
			UE_LOG(LogTemp, Error, TEXT("%s: 没有配置 OverlayWidgetControllerClass，请在 BP_KDHUD 里指定。"), *GetName());
			return nullptr;
		}

		OverlayWidgetController = NewObject<UKDOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	}

	return OverlayWidgetController;
}

void AKDHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// 服务器 PossessedBy 与客户端 OnRep_PlayerState 都会调用本函数，只允许创建一次。
	if (OverlayWidget)
	{
		return;
	}

	if (!OverlayWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: 没有配置 OverlayWidgetClass，请在 BP_KDHUD 里指定。"), *GetName());
		return;
	}

	const FKDWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UKDOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	if (!WidgetController)
	{
		return;
	}

	OverlayWidget = CreateWidget<UKDUserWidget>(GetWorld(), OverlayWidgetClass);
	if (!OverlayWidget)
	{
		return;
	}

	// MVC 生命周期：
	// 1. View 先拿到 Controller —— 蓝图这时才有 WidgetController，可以在 WidgetControllerSet 里绑定控件；
	// 2. Controller 推初始值、订阅属性变化；
	// 3. 最后才 AddToViewport，保证第一帧显示的就是正确数值。
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->InitWidgetController();
	OverlayWidget->AddToViewport();
}
