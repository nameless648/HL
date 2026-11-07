// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KDGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class KD_API UKDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "KD|Debug")
	bool bDrawDebug = false;
};
