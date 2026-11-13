// Fill out your copyright notice in the Description page of Project Settings.


#include "KDEnemyCharacter.h"
#include "KD/AbilitySystemComponent/KDAbilitySystemComponent.h"
#include "KD/AttributeSet/KDAttributeSet.h"


// Sets default values
AKDEnemyCharacter::AKDEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	EnemyAbilitySystemComponent = CreateDefaultSubobject<UKDAbilitySystemComponent>(FName("AbilitySystemComponent"));
	EnemyAbilitySystemComponent->SetIsReplicated(true);
	EnemyAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UKDAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AKDEnemyCharacter::GetAbilitySystemComponent() const
{
	return EnemyAbilitySystemComponent;
	
}


void AKDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	
	if (!HasAuthority()) return;
	
	GiveStartAbilities();
	InitializeAttributes();
}



