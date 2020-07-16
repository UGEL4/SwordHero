// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Components/SWH_HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USWH_HealthComponent::USWH_HealthComponent()
{
	HealthData = { 0.f, 100.f, 100.f };
}


void USWH_HealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage > 0.f)
	{
		ModifyHealthValue(-Damage, true);
		OnHealthChanged.Broadcast(this, HealthData.Current, Damage, DamageType, InstigatedBy, DamageCauser);
	}
}

// Called when the game starts
void USWH_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &USWH_HealthComponent::HandleTakeAnyDamage);
	}
	
}

void USWH_HealthComponent::UpdateHealthUI()
{
	BP_UpdateHealthUI();
}

void USWH_HealthComponent::SetHealthValue(float value, bool bUpdateUI)
{
	HealthData.Current = FMath::Clamp(value, HealthData.Min, HealthData.Max);
	if (bUpdateUI)
	{
		UpdateHealthUI();
	}
}

void USWH_HealthComponent::ModifyHealthValue(float value, bool bUpdateUI)
{
	if (value != 0)
	{
		float OldValue = HealthData.Current;
		SetHealthValue(OldValue + value, bUpdateUI);
	}
}
