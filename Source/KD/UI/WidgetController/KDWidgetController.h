// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "KDWidgetController.generated.h"

/**
 * 传给 WidgetController 的上下文：PlayerController / PlayerState / ASC / AttributeSet。
 * HUD 创建 Controller 时注入，Controller 之后不再自己去到处找这些对象。
 */
USTRUCT(BlueprintType)
struct FKDWidgetControllerParams
{
	GENERATED_BODY()

public:
	FKDWidgetControllerParams() {}
	FKDWidgetControllerParams(APlayerController* InPlayerController, APlayerState* InPlayerState,
		UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
		: PlayerController(InPlayerController)
		, PlayerState(InPlayerState)
		, AbilitySystemComponent(InAbilitySystemComponent)
		, AttributeSet(InAttributeSet) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * Controller 层（MVC 的 C）基类。
 *
 * Model 是 AttributeSet / ASC，View 是 UserWidget。View 只认识这个 Controller，
 * 由它把 Model 的数据变化翻译成蓝图可绑定的委托，View 不需要知道 GAS 的存在。
 */
UCLASS()
class KD_API UKDWidgetController : public UObject
{
	GENERATED_BODY()

public:
	/** 注入上下文参数。HUD 创建 Controller 后立刻调用。 */
	UFUNCTION(BlueprintCallable, Category = "KD|Widget Controller")
	void SetWidgetControllerParams(const FKDWidgetControllerParams& Params);

	/**
	 * 生命周期唯一入口：先推初始值，再订阅后续变化。
	 * 子类要加初始化步骤就重写这两个虚函数，不要再让 HUD 去知道内部顺序。
	 */
	virtual void InitWidgetController();

	/** 四个上下文是否齐全。子类可以按自己的依赖重写（敌人没有 PlayerController / PlayerState）。 */
	UFUNCTION(BlueprintPure, Category = "KD|Widget Controller")
	virtual bool AreParamsValid() const;

	/** 把当前值推给 View（第一次进游戏时用）。 */
	virtual void BroadcastInitialValues();

	/** 绑定属性变化，之后每次变化再推给 View。 */
	virtual void BindCallbacksToDependencies();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "KD|Widget Controller")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "KD|Widget Controller")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "KD|Widget Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "KD|Widget Controller")
	TObjectPtr<UAttributeSet> AttributeSet;
};
