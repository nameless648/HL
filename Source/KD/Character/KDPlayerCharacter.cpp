// Fill out your copyright notice in the Description page of Project Settings.


#include "KDPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KD/Core/KDPlayerState.h"
#include "KD/Core/KDPlayerController.h"
#include "KD/UI/KDHUD.h"


// Sets default values
AKDPlayerCharacter::AKDPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = true;
}

UAbilitySystemComponent* AKDPlayerCharacter::GetAbilitySystemComponent() const
{
	AKDPlayerState* KDPlayerState = Cast<AKDPlayerState>(GetPlayerState());
	if (!KDPlayerState) return nullptr;
	return KDPlayerState->GetAbilitySystemComponent();
}

//服务器
void AKDPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!IsValid(GetAbilitySystemComponent())||!HasAuthority()) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	GiveStartAbilities();
	InitializeAttributes();
	InitOverlay();
}

//客户端
void AKDPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);

	InitOverlay();
}

// 把 HUD 和 GAS 的上下文接起来。UI 层自己不负责查找 PC / PS / ASC。
void AKDPlayerCharacter::InitOverlay()
{
	AKDPlayerState* KDPlayerState = GetPlayerState<AKDPlayerState>();
	AKDPlayerController* KDPlayerController = Cast<AKDPlayerController>(GetController());
	if (!KDPlayerState || !KDPlayerController) return;

	if (AKDHUD* HUD = Cast<AKDHUD>(KDPlayerController->GetHUD()))
	{
		HUD->InitOverlay(KDPlayerController, KDPlayerState, GetAbilitySystemComponent(), KDPlayerState->GetAttributeSet());
	}
}



