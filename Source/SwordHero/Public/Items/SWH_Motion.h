// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SWH_Items.h"
#include "SWH_Motion.generated.h"

/**
 * 
 */
UCLASS()
class SWORDHERO_API USWH_Motion : public USWH_Items
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UAnimMontage* MontageToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PlayRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StartingPosition = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StartingSection = FName("None");
};
