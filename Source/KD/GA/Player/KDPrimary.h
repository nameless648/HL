// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KD/GA/KDGameplayAbility.h"
#include "KDPrimary.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class KD_API UKDPrimary : public UKDGameplayAbility
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable , Category = "KD|Ability")
	void HitBoxOverLapText();

	/** 命中时应用到目标的伤害效果（GE_PlayerDamage），在 GA_Primary 的 Class Defaults 里指定。 */
	UPROPERTY(EditDefaultsOnly , Category = "KD|Ability")
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;
	
private:
	void DrawHitBoxOverLapDebugs(const TArray<FOverlapResult> &OverlapResults,const FVector& HitBoxLocation) const;
	
	UPROPERTY(EditDefaultsOnly , Category = "KD|Ability")
	float HitBoxRadius = 100.0f;
	
	UPROPERTY(EditDefaultsOnly , Category = "KD|Ability")
	float HitBoxForwardOffset = 200.0f;
	
	UPROPERTY(EditDefaultsOnly , Category = "KD|Ability")
	float HitBoxElevationOffset = 20.0f;
};
