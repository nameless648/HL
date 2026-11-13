// Fill out your copyright notice in the Description page of Project Settings.


#include "KDPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KD/Core/KDPlayerState.h"


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
}

//客户端
void AKDPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	
}



