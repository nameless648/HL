// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
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
	
private:
	//ASC
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAttributeSet> AttributeSet ;
	
	//GA
	UPROPERTY(EditDefaultsOnly,Category="KD|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
};
