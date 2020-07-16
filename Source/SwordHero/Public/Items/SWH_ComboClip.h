// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SWH_AttackMotion.h"
#include "SWH_ComboClip.generated.h"

/**
 * 
 */
class ASWH_MotionActor;
UCLASS()
class SWORDHERO_API USWH_ComboClip : public USWH_AttackMotion
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USWH_ComboClip* NextCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USWH_ComboClip* BranchCombo;

	//skill class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ASWH_MotionActor> Skill;
};
