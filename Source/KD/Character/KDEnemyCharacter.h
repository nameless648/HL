// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KDCharacter.h"
#include "KD/AbilitySystemComponent/KDAbilitySystemComponent.h"
#include "KDEnemyCharacter.generated.h"

class UAttributeSet;

UCLASS()
class KD_API AKDEnemyCharacter : public AKDCharacter
{
	GENERATED_BODY()

public:
	AKDEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UKDAbilitySystemComponent> EnemyAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAttributeSet> AttributeSet ;
};
