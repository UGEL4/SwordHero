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
	TArray<FHitResult> HitResults;//保存命中结果//
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> HitActors;//保存命中的Actor//
	UPROPERTY()
	AController* EventInstigator;//ApplyDamage函数参数//
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType>DamageTypeClass;//ApplyDamage函数参数//
	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> LastLocations;//插槽位置//
	UPROPERTY()
	class AHero1* Player;//当前玩家//
	UPROPERTY()
	class ASWH_BaseWeaponClass* Weapon;//玩家武器//
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;//射线忽略目标//
public:
	//Functions
	UFUNCTION()
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)override;//Tick//
	UFUNCTION()
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)override;//通知结束//
	UFUNCTION()
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)override;//通知开始//
};
