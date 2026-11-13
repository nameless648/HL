// Fill out your copyright notice in the Description page of Project Settings.


#include "KDPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "KD/GameplayTags/KDTags.h"


void AKDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSubsystem))
	{
		for(UInputMappingContext* context : InputMappingContext)
		{
			InputSubsystem ->AddMappingContext(context , 0 ); 
		}
	}
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		//在这里绑定输入操作和回调函数
		if (MoveAction) {
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKDPlayerController::Move);
		} 
		if (LookAction) {
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKDPlayerController::Look);
		}
		if (JumpAction) {
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AKDPlayerController::Jump);
		}
		if (JumpAction) {
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AKDPlayerController::StopJumping);
		}
		if (PrimaryAction) {
			EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &AKDPlayerController::Primary);
		}
		if (SecondaryAction)
		{
			EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &AKDPlayerController::Secondary);
		}
		if (TertiaryAction)
		{
			EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Triggered, this, &AKDPlayerController::Tertiary);
		}
	}	
}

void AKDPlayerController::Move(const FInputActionValue& Value)
{
	//从输入操作值中获取移动向量
	FVector2D MoveVector = Value.Get<FVector2D>();

	//获取Pawn对象，并将移动向量应用到Pawn上，实现移动
	if (APawn* ControllerPawn = GetPawn()) {
		//将移动向量转换为世界空间的移动方向
		FRotator YawControlRotation = GetControlRotation();
		//计算前向和右向的移动方向
		FVector Forward = FRotationMatrix(YawControlRotation).GetScaledAxis(EAxis::X);
		FVector Right = FRotationMatrix(YawControlRotation).GetScaledAxis(EAxis::Y);
		//将移动向量应用到Pawn上，实现移动
		ControllerPawn->AddMovementInput(Forward, MoveVector.Y);
		ControllerPawn->AddMovementInput(Right, MoveVector.X);
	}
}

void AKDPlayerController::Look(const FInputActionValue& Value)
{
	// 输入为 Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (IsValid(this))
	{
		// 将偏航和俯仰输入添加到控制器
		this->AddYawInput(LookAxisVector.X);
		this->AddPitchInput(LookAxisVector.Y);
	}
}

void AKDPlayerController::Jump()
{
	GetCharacter()->Jump();
}

void AKDPlayerController::StopJumping()
{
	GetCharacter()->StopJumping();
}

void AKDPlayerController::Primary()
{
	ActivateAbility(KDTags::KDAbilities::Primary);
}

void AKDPlayerController::Secondary()
{
	ActivateAbility(KDTags::KDAbilities::Secondary);
}

void AKDPlayerController::Tertiary()
{
	ActivateAbility(KDTags::KDAbilities::Tertiary);
}

void AKDPlayerController::ActivateAbility(const FGameplayTag& AbilityTag)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	
	if (!IsValid(ASC)) return;
	
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}


