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



