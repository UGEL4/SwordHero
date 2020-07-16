// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Types/SWH_Types.h"
#include "SWH_Clip.generated.h"

/**
 * 
 */
UCLASS()
class SWORDHERO_API USWH_Clip : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	USWH_Clip* NextClip;
	UPROPERTY()
	USWH_Clip* BranchClip;

	UPROPERTY(BlueprintReadOnly)
	class USWH_ComboClip* ComboClipData;

	//�Ƿ�����ʼ��һ�ι���
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool AllowNextAttack = false;

	//��ϰ�����ͬʱ���£�
	FSWH_ComposeKeyStruct NextComboComposeKeyStruct;
	UPROPERTY()
	FSWH_ComposeKeyStruct BranchComboComposeKeyStruct;
	bool Okay;

public:
	void ConstructComposeKeys();
	void ConstructFirstComboComposeKeys(class USWH_ComboTree* FirstComboData);
};
