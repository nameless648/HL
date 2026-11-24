// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "KDMenuWidget.generated.h"

/**
 * 所有菜单的 C++ 基类。
 * 激活时接管输入和鼠标，关闭时还回去 —— 对应 Lyra 里 ActivatableWidget 的职责。
 */
UCLASS()
class KD_API UKDMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	/** 蓝图做内容层的事情（动画、刷新文本等）。 */
	UFUNCTION(BlueprintImplementableEvent, Category = "KD|UI")
	void BP_OnMenuActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "KD|UI")
	void BP_OnMenuDeactivated();

	/** 蓝图里指定默认聚焦的按钮（可选）。 */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UWidget> DefaultFocusWidget;
};
