// Fill out your copyright notice in the Description page of Project Settings.


#include "KDBlueprintLibrary.h"

EHitDirection UKDBlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}

	if (Dot > 0.5f)
	{
		return EHitDirection::Forward;
	}

	// 前后不明确时，用叉积判断左右
	const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
	if (Cross.Z < 0.f)
	{
		return EHitDirection::Left;
	}

	return EHitDirection::Right;
}

FName UKDBlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Forward: return FName("Forward");
	case EHitDirection::Back: return FName("Back");
	default: return FName("Unknown");
	}
}
