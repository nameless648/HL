// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "KDPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class KD_API AKDPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AKDPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** UI 层需要 AttributeSet 来广播初始值。 */
	UAttributeSet* GetAttributeSet() const;
	
private:
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere,Category="KD|Abilities")
	TObjectPtr<UAttributeSet> AttributeSet ;
};
