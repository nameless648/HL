// Fill out your copyright notice in the Description page of Project Settings.

#include "KDUserWidget.h"
#include "KD/UI/WidgetController/KDWidgetController.h"

void UKDUserWidget::SetWidgetController(UKDWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;

	// 通知蓝图：Controller 已就位，可以去绑定委托、刷新初始显示了。
	WidgetControllerSet();
}
