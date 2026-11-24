// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "KDHUDLayout.generated.h"

class UCommonActivatableWidgetStack;
class UCommonActivatableWidgetContainerBase;
class UKDMenuWidget;

/**
 * HUD 根布局（对应 Lyra 的 HUD Layout）。
 *
 * 三个层各一个栈：Game / Menu / Modal（标签见 KDTags::UI::Layer）。
 * 菜单的开关由 UKDUIManagerSubsystem 统一调度，Layout 只负责「层 → 栈」的映射。
 */
UCLASS()
class KD_API UKDHUDLayout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	/** 往指定层压一个菜单，返回实例。 */
	UKDMenuWidget* PushMenuToLayer(TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer);

	/** 关掉指定层最上面的菜单。 */
	void PopMenuFromLayer(FGameplayTag Layer);

	/** 清空指定层。 */
	void ClearLayer(FGameplayTag Layer);

	UKDMenuWidget* GetActiveMenu(FGameplayTag Layer) const;
	bool HasMenuInLayer(FGameplayTag Layer) const;
	bool IsMenuActiveInLayer(TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer) const;

protected:
	// 注册到 UIManager：Layout 活着的时候，UIManager 才能按玩家找到它。
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/** 蓝图里拖 CommonActivatableWidgetStack，名字必须一致。三个都是可选的。 */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UCommonActivatableWidgetStack> GameStack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UCommonActivatableWidgetStack> ModalStack;

	/** 按层标签取对应的栈。 */
	UCommonActivatableWidgetContainerBase* GetStack(FGameplayTag Layer) const;
};
