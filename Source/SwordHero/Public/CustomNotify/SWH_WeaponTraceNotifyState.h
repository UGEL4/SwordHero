// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SWH_WeaponTraceNotifyState.generated.h"

/**
 * 
 */

UCLASS()
class SWORDHERO_API USWH_WeaponTraceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	//Properties
	UPROPERTY(BlueprintReadOnly)
	TArray<FHitResult> HitResults;//�������н��//
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> HitActors;//�������е�Actor//
	UPROPERTY()
	AController* EventInstigator;//ApplyDamage��������//
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType>DamageTypeClass;//ApplyDamage��������//
	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> LastLocations;//���λ��//
	UPROPERTY()
	class AHero1* Player;//��ǰ���//
	UPROPERTY()
	class ASWH_BaseWeaponClass* Weapon;//�������//
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;//���ߺ���Ŀ��//
public:
	//Functions
	UFUNCTION()
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)override;//Tick//
	UFUNCTION()
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)override;//֪ͨ����//
	UFUNCTION()
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)override;//֪ͨ��ʼ//
};
