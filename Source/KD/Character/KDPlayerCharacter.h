// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KDCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "KDPlayerCharacter.generated.h"


UCLASS()
class KD_API AKDPlayerCharacter : public AKDCharacter
{
	GENERATED_BODY()

public:
	AKDPlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	
	UPROPERTY(VisibleAnywhere ,Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere ,Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;	
};
