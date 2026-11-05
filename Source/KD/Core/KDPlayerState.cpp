// Fill out your copyright notice in the Description page of Project Settings.
#include "KDPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

AKDPlayerState::AKDPlayerState()
{
	SetNetUpdateFrequency( 100.0f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AKDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
