// Fill out your copyright notice in the Description page of Project Settings.
#include "KDPlayerState.h"
#include "KD/AbilitySystemComponent/KDAbilitySystemComponent.h"
#include "KD/AttributeSet/KDAttributeSet.h"

AKDPlayerState::AKDPlayerState()
{
	SetNetUpdateFrequency( 100.0f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UKDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UKDAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AKDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
