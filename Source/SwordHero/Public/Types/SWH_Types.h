// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWH_Types.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESWH_FPropertyName : uint8
{
	EPropertyHP UMETA(DisplayName = "HP")
};

UENUM(BlueprintType)
enum class ESWH_FInputDirection : uint8
{
	ENone UMETA(DisplayName = "None"),
	EForward UMETA(DisplayName = "Forward"),
	EBack UMETA(DisplayName = "Back")
};

UENUM(BlueprintType)
enum class ESWH_AIStateName : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Combat UMETA(DisplayName = "Combat"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Dodge UMETA(DisplayName = "Dodge"),
	E_MoveAround UMETA(DisplayName = "MoveAround"),
	E_Defense UMETA(DisplayName = "Defense")
};


USTRUCT(BlueprintType)
struct FSWH_PropertyValue
{
	GENERATED_USTRUCT_BODY()UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Min;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Current;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Max;
};

//技能需要输入的指令的结构体
USTRUCT(BlueprintType)
struct FSWH_SkillInputStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FKey Key;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float inputTime = 0.5f;
};

USTRUCT(BlueprintType)
struct FSWH_AttackMotionStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName AttackMotionName;

	//下一个连击动作触发按键
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FKey> NextAttackMotionKeys;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	ESWH_FInputDirection NextAttackDirectionInput;
	//分支连击动作触发按键
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FKey> BranchAttackMotionKeys;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	ESWH_FInputDirection BranchAttackDirectionInput;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ComposeKeysInputTime;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float AttackDamageAmount;
};

USTRUCT(BlueprintType)
struct FSWH_ComposeKeyStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FKey> ComposeKeys;

	bool Okay = false;

public:
	void CheckKey(struct FKey key);
};

USTRUCT(BlueprintType)
struct FSWH_BoxTraceSocketStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName TraceSocketName;
	//UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	//FVector TraceSocketLoaction;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector HalfSize;
};

USTRUCT(BlueprintType)
struct FSWH_AnimData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<class UAnimMontage*> AnimMontages;
};

USTRUCT(BlueprintType)
struct FSWH_AnimDataMap
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<ESWH_AIStateName, FSWH_AnimData> AnimMontageMap;
};