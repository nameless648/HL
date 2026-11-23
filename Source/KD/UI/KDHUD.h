// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widget/KDUserWidget.h"
#include "WidgetController/KDOverlayWidgetController.h"
#include "KDHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * UI 的装配者（Aura 的 MVC 里由 HUD 承担）：
 * 创建 View（OverlayWidget）、创建 Controller、注入上下文，然后交给 Controller 自己走生命周期。
 */
UCLASS()
class KD_API AKDHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** 取（或创建）Overlay 的 Controller。同一个 HUD 生命周期内只创建一次。 */
	UKDOverlayWidgetController* GetOverlayWidgetController(const FKDWidgetControllerParams& WidgetControllerParams);

	/**
	 * UI 初始化入口。
	 * 服务器 PossessedBy 和客户端 OnRep_PlayerState 都会走到这里，内部做了幂等，
	 * 第二次调用直接返回，不会叠出两层 Overlay。
	 */
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	/** 已经创建出来的 Overlay，未初始化时为 nullptr。 */
	UKDUserWidget* GetOverlayWidget() const { return OverlayWidget; }

protected:
	/** 指向 WBP_Overlay（父类 UKDUserWidget），在 BP_KDHUD 里指定。 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KD|UI")
	TSubclassOf<UKDUserWidget> OverlayWidgetClass;

	/** 指向 BP_KDOverlayWidgetController（父类 UKDOverlayWidgetController），在 BP_KDHUD 里指定。 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KD|UI")
	TSubclassOf<UKDOverlayWidgetController> OverlayWidgetControllerClass;

private:
	UPROPERTY()
	TObjectPtr<UKDUserWidget> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UKDOverlayWidgetController> OverlayWidgetController;
};
