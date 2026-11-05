// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "KDPlayerController.generated.h"


struct FInputActionValue;

UCLASS()
class KD_API AKDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override ;
	
private:
	//增强输入资产
	UPROPERTY(EditDefaultsOnly , Category="KD|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly , Category="KD|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;

	//回调函数
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void Primary();
};
