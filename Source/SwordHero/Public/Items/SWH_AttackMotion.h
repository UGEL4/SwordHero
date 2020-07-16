// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SWH_Motion.h"
#include  "../Types/SWH_Types.h"
#include "SWH_AttackMotion.generated.h"

/**
 * 
 */
UCLASS()
class SWORDHERO_API USWH_AttackMotion : public USWH_Motion
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSWH_AttackMotionStruct AttackMotionData;
};
