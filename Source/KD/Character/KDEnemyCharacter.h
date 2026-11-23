// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KDCharacter.h"
#include "KD/AbilitySystemComponent/KDAbilitySystemComponent.h"
#include "KDEnemyCharacter.generated.h"

class UAttributeSet;
class UWidgetComponent;
class UKDUserWidget;

UCLASS()
class KD_API AKDEnemyCharacter : public AKDCharacter
{
	GENERATED_BODY()

public:
	AKDEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;

	/** 找到身上的 WidgetComponent，把本敌人的 ASC / AttributeSet 注入给 Controller。 */
	void InitHealthBar();

	/** 血条控件类（父类 KDUserWidget）。组件的 Widget Class 没配时用它兜底。 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KD|UI")
	TSubclassOf<UKDUserWidget> HealthBarWidgetClass;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UKDAbilitySystemComponent> EnemyAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAttributeSet> AttributeSet ;
};
