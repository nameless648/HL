// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KD/GA/KDGameplayAbility.h"
#include "KDHitReact.generated.h"

/**
 * 
 */
UCLASS()
class KD_API UKDHitReact : public UKDGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "KD|Ability")
	void CacheHitDirectionVectors(AActor* Instigator);

	UPROPERTY(BlueprintReadOnly, Category = "KD|Ability")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "KD|Ability")
	FVector ToInstigator;
};
