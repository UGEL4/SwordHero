// Fill out your copyright notice in the Description page of Project Settings.

#include "SingleSword.h"
#include "../../SwordHero.h"
#include "ComboInputComponent/SWH_ComboInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Particles/ParticleSystem.h"
//#include "UObject/ConstructorHelpers.h"

// Sets default values
ASingleSword::ASingleSword()
{
	//Super();
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//static FObjectFinder<UStaticMesh> MeshAssert(TEXT("/Game/Weapons/Mesh/Sword"));
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Weapons/Mesh/Sword"));
	SwordMeshComp->SetStaticMesh(Mesh.Object);*/
	//ComboInputComponent = CreateDefaultSubobject<USWH_ComboInputComponent>(TEXT("ComboInputComponent"));
}

void ASingleSword::InitComboInputComponent(ACharacter* owner)
{
	if (ComboInputComponentClass)
	{
		ComboInputComponent = Cast<USWH_ComboInputComponent>(GetComponentByClass(ComboInputComponentClass));
		ComboInputComponent->Init(owner);
	}
}

// Called when the game starts or when spawned
void ASingleSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASingleSword::Attack(struct FKey key, ESWH_FInputDirection Direction)
{
	if (ComboInputComponent)
	{
		ComboInputComponent->KeyReleased(key, Direction);
	}
}

void ASingleSword::CheckInput(struct FKey key)
{
	if (ComboInputComponent)
	{
		ComboInputComponent->CheckInputKey(key);
		/*UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HumanBodyBloodEffect, RootComponent->GetSocketLocation(BoxTraceSocketData[0].TraceSocketName),
			RootComponent->GetSocketRotation(BoxTraceSocketData[0].TraceSocketName),true);*/
	}
}

void ASingleSword::PlayHitEffect(FHitResult* HitResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, HitResult->Actor->GetFName().ToString());
	EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult->PhysMaterial.Get());
	UParticleSystem* SelectEffect = nullptr;
	switch (SurfaceType)
	{
	case HUMAN_BODY_SURFACE:
		SelectEffect = HumanBodyBloodEffect;
		break;
	default:
		SelectEffect = DefaultEffect;
		break;
	}

	if (SelectEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), SelectEffect,
			HitResult->ImpactPoint,
			HitResult->ImpactNormal.Rotation());
	}
}

