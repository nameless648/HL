// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "KDCharacter.generated.h"

UCLASS()
class KD_API AKDCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKDCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAttributeSet> AttributeSet ;
};
