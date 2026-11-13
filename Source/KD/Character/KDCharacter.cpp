// Fill out your copyright notice in the Description page of Project Settings.


#include "KDCharacter.h"
#include "AbilitySystemComponent.h"


// Sets default values
AKDCharacter::AKDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AKDCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

//GA激活函数
void AKDCharacter::GiveStartAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	for (const auto & Ability : StartAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void AKDCharacter::InitializeAttributes()const
{
	checkf (IsValid(InitializeAttributeEffect),TEXT("Initialize Attribute Effect Failed"));
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributeEffect, 1,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
		
}



