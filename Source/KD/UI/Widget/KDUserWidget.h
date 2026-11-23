// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KDUserWidget.generated.h"

class UKDWidgetController;

/**
 * View 层（MVC 的 V）基类。
 *
 * 它只认识 UKDWidgetController，不直接碰 AttributeSet / GAS：
 * 具体显示什么，由 Controller 通过委托推过来。
 */
UCLASS()
class KD_API UKDUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * View 的唯一入口：保存 Controller 并触发蓝图事件。
	 * 声明为 virtual，蓝图子类或 C++ 子类需要额外初始化时可以重写。
	 */
	UFUNCTION(BlueprintCallable, Category = "KD|UI")
	virtual void SetWidgetController(UKDWidgetController* InWidgetController);

	UPROPERTY(BlueprintReadOnly, Category = "KD|UI")
	TObjectPtr<UKDWidgetController> WidgetController;

protected:
	/**
	 * 蓝图事件：Controller 已经就位。
	 * 在这里把 OnHealthChanged 之类的委托绑到具体的进度条 / 文本上。
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "KD|UI")
	void WidgetControllerSet();
};
