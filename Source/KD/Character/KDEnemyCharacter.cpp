// Fill out your copyright notice in the Description page of Project Settings.


#include "KDEnemyCharacter.h"
#include "KD/AbilitySystemComponent/KDAbilitySystemComponent.h"
#include "KD/AttributeSet/KDAttributeSet.h"
#include "KD/UI/Widget/KDUserWidget.h"
#include "KD/UI/WidgetController/KDEnemyWidgetController.h"
#include "Components/WidgetComponent.h"


// Sets default values
AKDEnemyCharacter::AKDEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	EnemyAbilitySystemComponent = CreateDefaultSubobject<UKDAbilitySystemComponent>(FName("AbilitySystemComponent"));
	EnemyAbilitySystemComponent->SetIsReplicated(true);
	EnemyAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UKDAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AKDEnemyCharacter::GetAbilitySystemComponent() const
{
	return EnemyAbilitySystemComponent;
	
}


void AKDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);

	// 客户端也要显示血条，所以放在 HasAuthority 判断之前。
	InitHealthBar();
	
	if (!HasAuthority()) return;
	
	GiveStartAbilities();
	InitializeAttributes();
}

void AKDEnemyCharacter::InitHealthBar()
{
	// 血条组件由蓝图挂在敌人身上（BP_Enemy_Base 的 HealthBar），这里只负责注入数据。
	TArray<UWidgetComponent*> WidgetComponents;
	GetComponents<UWidgetComponent>(WidgetComponents);
	if (WidgetComponents.Num() == 0)
	{
		return;
	}

	UWidgetComponent* HealthBarComponent = WidgetComponents[0];
	if (!HealthBarComponent)
	{
		return;
	}

	// 组件自己没配 Widget Class 时，用 C++ 属性兜底。
	if (HealthBarWidgetClass && !HealthBarComponent->GetWidgetClass())
	{
		HealthBarComponent->SetWidgetClass(HealthBarWidgetClass);
	}

	if (!HealthBarComponent->GetUserWidgetObject())
	{
		HealthBarComponent->InitWidget();
	}

	UKDUserWidget* HealthBarWidget = Cast<UKDUserWidget>(HealthBarComponent->GetUserWidgetObject());
	if (!HealthBarWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: 血条 WidgetComponent 没有创建出 UKDUserWidget，检查 Widget Class。"), *GetName());
		return;
	}

	// 敌人的 Controller 只依赖 Character 自己的 ASC / AttributeSet。
	UKDEnemyWidgetController* EnemyWidgetController = NewObject<UKDEnemyWidgetController>(this);
	EnemyWidgetController->SetWidgetControllerParams(
		FKDWidgetControllerParams(nullptr, nullptr, EnemyAbilitySystemComponent, AttributeSet));

	HealthBarWidget->SetWidgetController(EnemyWidgetController);
	EnemyWidgetController->InitWidgetController();
}
