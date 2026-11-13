// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "KDCharacter.generated.h"

class UGameplayAbility;

UCLASS(Abstract)
class KD_API AKDCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKDCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	
	void GiveStartAbilities();
	void InitializeAttributes()const;
	
private:

	//GA
	UPROPERTY(EditDefaultsOnly,Category="KD|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditDefaultsOnly,Category="KD|Abilities")
	TSubclassOf<UGameplayEffect> InitializeAttributeEffect;
};
