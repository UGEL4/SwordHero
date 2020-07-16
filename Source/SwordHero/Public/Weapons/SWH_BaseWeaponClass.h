// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "../Types/SWH_Types.h"
#include "SWH_BaseWeaponClass.generated.h"

class USWH_ComboInputComponent;
class UParticleSystem;
UCLASS(Abstract)
class SWORDHERO_API ASWH_BaseWeaponClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWH_BaseWeaponClass();
	virtual void InitComboInputComponent(class ACharacter* owner);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo Input Component", meta = (AllowPrivateAccess = "true"))
	USWH_ComboInputComponent* ComboInputComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo Input Component", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USWH_ComboInputComponent> ComboInputComponentClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* SwordMeshComp;

	//±≥≤ø≤Â≤€
	UPROPERTY(EditDefaultsOnly, Category = "Mesh | Socket")
	FName RootSocketName;
	// ÷≤ø≤Â≤€
	UPROPERTY(EditDefaultsOnly, Category = "Mesh | Socket")
	FName HandSocketName;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh | Socket")
	TArray<FSWH_BoxTraceSocketStruct> BoxTraceSocketData;

	UPROPERTY(BlueprintReadWrite)
	float DamageValue;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	ACharacter* WeaponOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* DefaultEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* HumanBodyBloodEffect;

	UPROPERTY(BlueprintReadOnly)
	TMap<AActor*,FName> HitBoneMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack(struct FKey key, ESWH_FInputDirection Direction);
	virtual void CheckInput(struct FKey key);
	virtual void PlayHitEffect(FHitResult* HitResult);

	FORCEINLINE class UStaticMeshComponent* GetWeaponMesh() const { return SwordMeshComp; }
	FORCEINLINE const TArray<FSWH_BoxTraceSocketStruct>& GetBoxTraceSocketData() const { return BoxTraceSocketData; }
	FORCEINLINE float GetDamageValue() const { return DamageValue; }
	FORCEINLINE const FName& GetRootSocketName() const { return RootSocketName; }
	FORCEINLINE virtual ACharacter* GetWeaponOwner() const { return WeaponOwner; }
	FORCEINLINE virtual void SetWeaponOwner(class ACharacter* owner) { WeaponOwner = owner; }
	FORCEINLINE void SetHitBoneMap(AActor* Actor, FName BoneName) { HitBoneMap.Add(Actor,BoneName); }
};
