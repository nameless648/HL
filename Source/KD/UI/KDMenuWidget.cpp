// Fill out your copyright notice in the Description page of Project Settings.

#include "KDMenuWidget.h"
#include "Components/Widget.h"
#include "GameFramework/PlayerController.h"

void UKDMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	// 菜单打开：GameAndUI 让鼠标能点 UI，同时保留游戏输入（B/Esc 才能继续被 PlayerController 收到）。
	// 角色移动/视角在这里关掉，攻击/跳跃在 PlayerController 里根据 HasMenu 拦。
	if (APlayerController* PC = GetOwningPlayer())
	{
		FInputModeGameAndUI InputMode;
		if (DefaultFocusWidget)
		{
			InputMode.SetWidgetToFocus(DefaultFocusWidget->TakeWidget());
		}
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(true);

		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);
	}

	BP_OnMenuActivated();
}

void UKDMenuWidget::NativeOnDeactivated()
{
	BP_OnMenuDeactivated();

	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);
		PC->SetInputMode(FInputModeGameOnly());
		PC->SetShowMouseCursor(false);
	}

	Super::NativeOnDeactivated();
}

UWidget* UKDMenuWidget::NativeGetDesiredFocusTarget() const
{
	if (DefaultFocusWidget)
	{
		return DefaultFocusWidget.Get();
	}

	return Super::NativeGetDesiredFocusTarget();
}
