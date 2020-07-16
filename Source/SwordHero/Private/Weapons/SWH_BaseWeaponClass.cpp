// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Weapons/SWH_BaseWeaponClass.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
// Sets default values
ASWH_BaseWeaponClass::ASWH_BaseWeaponClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SwordMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = SwordMeshComp;
	DamageValue = 0.f;
}

void ASWH_BaseWeaponClass::InitComboInputComponent(ACharacter* owner)
{
	
}

// Called when the game starts or when spawned
void ASWH_BaseWeaponClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASWH_BaseWeaponClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASWH_BaseWeaponClass::Attack(struct FKey key, ESWH_FInputDirection Direction)
{

}

void ASWH_BaseWeaponClass::CheckInput(struct FKey key)
{

}

void ASWH_BaseWeaponClass::PlayHitEffect(FHitResult* HitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Base weapon effect"));
}

