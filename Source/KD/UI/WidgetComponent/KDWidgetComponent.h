// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "KDWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KD_API UKDWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


};
