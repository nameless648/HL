// Fill out your copyright notice in the Description page of Project Settings.


#include "KDPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "KD/GameplayTags/KDTags.h"
#include "KD/UI/KDHUDLayout.h"
#include "KD/UI/KDMenuWidget.h"
#include "KD/UI/KDUIManagerSubsystem.h"


void AKDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 菜单的根布局：整局只创建一次，菜单由它内部的 Stack 管理。
	if (HUDLayoutClass)
	{
		HUDLayout = CreateWidget<UKDHUDLayout>(this, HUDLayoutClass);
		if (HUDLayout)
		{
			HUDLayout->AddToViewport();
		}
	}
}

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
		if (PauseAction)
		{
			EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AKDPlayerController::TogglePauseMenu);
		}
		if (InventoryAction)
		{
			EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AKDPlayerController::ToggleInventoryMenu);
		}
	}	
}

bool AKDPlayerController::IsMenuOpen() const
{
	const UKDUIManagerSubsystem* UIManager = UKDUIManagerSubsystem::Get(this);
	if (!UIManager)
	{
		return false;
	}

	APlayerController* Self = const_cast<AKDPlayerController*>(this);
	return UIManager->HasMenu(Self, KDTags::UI::Layer::Menu)
		|| UIManager->HasMenu(Self, KDTags::UI::Layer::Modal);
}

void AKDPlayerController::ToggleMenu(TSubclassOf<UKDMenuWidget> MenuClass, FGameplayTag Layer)
{
	if (UKDUIManagerSubsystem* UIManager = UKDUIManagerSubsystem::Get(this))
	{
		UIManager->ToggleMenu(this, MenuClass, Layer);
	}
}

void AKDPlayerController::TogglePauseMenu()
{
	ToggleMenu(PauseMenuClass, KDTags::UI::Layer::Menu);
}

void AKDPlayerController::ToggleInventoryMenu()
{
	ToggleMenu(InventoryMenuClass, KDTags::UI::Layer::Menu);
}

void AKDPlayerController::Move(const FInputActionValue& Value)
{
	if (IsMenuOpen())
	{
		return;
	}

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
	if (IsMenuOpen())
	{
		return;
	}

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
	if (IsMenuOpen() || !GetCharacter())
	{
		return;
	}

	GetCharacter()->Jump();
}

void AKDPlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void AKDPlayerController::Primary()
{
	if (IsMenuOpen())
	{
		return;
	}

	ActivateAbility(KDTags::KDAbilities::Primary);
}

void AKDPlayerController::Secondary()
{
	if (IsMenuOpen())
	{
		return;
	}

	ActivateAbility(KDTags::KDAbilities::Secondary);
}

void AKDPlayerController::Tertiary()
{
	if (IsMenuOpen())
	{
		return;
	}

	ActivateAbility(KDTags::KDAbilities::Tertiary);
}

void AKDPlayerController::ActivateAbility(const FGameplayTag& AbilityTag)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	
	if (!IsValid(ASC)) return;
	
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}
