// Fill out your copyright notice in the Description page of Project Settings.


#include "KDPrimary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "GameplayEffect.h"
#include "KD/GameplayTags/KDTags.h"

void UKDPrimary::HitBoxOverLapText()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	// 忽略自身，避免重叠检测把自己算进结果
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);

	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);
    //碰撞发送事件
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!Result.GetActor()) continue;

		// 先造成伤害：用自身 ASC 创建伤害 GE 的 Spec，应用到目标 ASC。
		if (DamageGameplayEffect)
		{
			UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Result.GetActor());
			if (SourceASC && TargetASC)
			{
				FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
				ContextHandle.AddSourceObject(this);

				FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageGameplayEffect, GetAbilityLevel(), ContextHandle);
				if (SpecHandle.IsValid())
				{
					SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
				}
			}
		}

		FGameplayEventData PayLoad;
		PayLoad.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Result.GetActor() , KDTags::Event::Enemy::HitReact ,PayLoad );
	}
	
	if (bDrawDebug)
	{
		DrawHitBoxOverLapDebugs(OverlapResults,HitBoxLocation);
		
	}
}

void UKDPrimary::DrawHitBoxOverLapDebugs(const TArray<FOverlapResult>& OverlapResults,const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);

	for (const FOverlapResult& Result : OverlapResults)
	{
		if (IsValid(Result.GetActor()))
		{
			FVector DebugLocation = Result.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
			DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 10, FColor::Green, false, 3.f);
		}
	}
}
