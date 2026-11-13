// Fill out your copyright notice in the Description page of Project Settings.


#include "KDHitReact.h"

void UKDHitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();

	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();

	ToInstigator = (InstigatorLocation - AvatarLocation).GetSafeNormal();
}
