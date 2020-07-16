// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SWH_Items.h"
#include "../Types/SWH_Types.h"
#include "SWH_ComboTree.generated.h"

/**
 * 
 */
class ACharacter;
UCLASS()
class SWORDHERO_API USWH_ComboTree : public USWH_Items
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USWH_ComboClip* FirstCombClip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ComboTreeName = FName("None");
	//���������ȼ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Priority;
	//��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FKey> ActionKeys;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bHold;
	/*UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float HoldTime;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ComposeKeysInputTime;*/

	//��������(�����)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESWH_FInputDirection AnotherKey;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ACharacter> SkillTreeOwner;
};
