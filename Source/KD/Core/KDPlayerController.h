// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "KDPlayerController.generated.h"

class UKDHUDLayout;
class UKDMenuWidget;

struct FInputActionValue;

UCLASS()
class KD_API AKDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/** 打开 / 关闭暂停菜单；已经开着就关，开着别的菜单就切过去。 */
	UFUNCTION(BlueprintCallable, Category = "KD|UI")
	void TogglePauseMenu();

	/** 打开 / 关闭背包；已经开着就关，开着别的菜单就切过去。 */
	UFUNCTION(BlueprintCallable, Category = "KD|UI")
	void ToggleInventoryMenu();

protected:
	virtual void SetupInputComponent() override ;
	
private:
	// 菜单用的 HUD 布局与菜单类
	UPROPERTY(EditDefaultsOnly, Category = "KD|UI")
	TSubclassOf<UKDHUDLayout> HUDLayoutClass;

	UPROPERTY(EditDefaultsOnly, Category = "KD|UI")
	TSubclassOf<UKDMenuWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "KD|UI")
	TSubclassOf<UKDMenuWidget> InventoryMenuClass;


	//增强输入资产
	UPROPERTY()
	TObjectPtr<UKDHUDLayout> HUDLayout;

	UPROPERTY(EditDefaultsOnly, Category = "KD|Input")
	TObjectPtr<UInputAction> PauseAction;

	UPROPERTY(EditDefaultsOnly, Category = "KD|Input")
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditDefaultsOnly , Category="KD|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Abilities")
	TObjectPtr<UInputAction> SecondaryAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Abilities")
	TObjectPtr<UInputAction> TertiaryAction;

	/** 所有菜单开关都走 UIManager；Layer 决定进哪个栈。 */
	void ToggleMenu(TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer);

	/** 有菜单打开时，角色输入全部忽略。 */
	bool IsMenuOpen() const;

	//回调函数
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void Primary();
	void Secondary();
	void Tertiary();
	void ActivateAbility(const FGameplayTag& AbilityTag);
};
