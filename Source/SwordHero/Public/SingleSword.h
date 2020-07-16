// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/SWH_Types.h"
#include "Weapons/SWH_BaseWeaponClass.h"
#include "SingleSword.generated.h"

UCLASS(Abstract)
class SWORDHERO_API ASingleSword : public ASWH_BaseWeaponClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleSword();
	void InitComboInputComponent(class ACharacter* owner) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack(struct FKey key, ESWH_FInputDirection Direction) override;
	virtual void CheckInput(struct FKey key) override;
	void PlayHitEffect(FHitResult* HitResult) override;

	//FORCEINLINE class ACharacter* GetWeaponOwner() const override { return WeaponOwner; }
	//FORCEINLINE void SetWeaponOwner(class ACharacter* owner) override { WeaponOwner = owner; }
};
