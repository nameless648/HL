// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "KDUIManagerSubsystem.generated.h"

class APlayerController;
class UKDHUDLayout;
class UKDMenuWidget;

/**
 * UI 管理器（对应 Lyra 的 UIManagerSubsystem）。
 *
 * 职责：记住每个玩家当前的 UKDHUDLayout，按「层」把菜单压进对应的栈。
 * 它不认识任何具体菜单，只认识层标签和 UKDMenuWidget 基类。
 */
UCLASS()
class KD_API UKDUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UKDUIManagerSubsystem* Get(const UObject* WorldContextObject);

	/** HUDLayout 在 Construct 时注册、Destruct 时注销。 */
	void RegisterLayout(APlayerController* PC, UKDHUDLayout* Layout);
	void UnregisterLayout(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "KD|UI")
	UKDMenuWidget* PushMenu(APlayerController* PC, TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer);

	UFUNCTION(BlueprintCallable, Category = "KD|UI")
	void PopMenu(APlayerController* PC, FGameplayTag Layer);

	/** 当前层就是这类菜单 → 关掉并返回 false；否则清层再打开并返回 true。 */
	UFUNCTION(BlueprintCallable, Category = "KD|UI")
	bool ToggleMenu(APlayerController* PC, TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer);

	UFUNCTION(BlueprintPure, Category = "KD|UI")
	bool HasMenu(APlayerController* PC, FGameplayTag Layer) const;

private:
	UKDHUDLayout* FindLayout(APlayerController* PC) const;

	TMap<TWeakObjectPtr<APlayerController>, TWeakObjectPtr<UKDHUDLayout>> Layouts;
};
