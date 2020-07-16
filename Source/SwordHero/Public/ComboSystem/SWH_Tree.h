// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Types/SWH_Types.h"
#include "SWH_Tree.generated.h"

/**
 * 
 */
UCLASS()
class SWORDHERO_API USWH_Tree : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USWH_Clip* ComboClipHead;
	UPROPERTY(BlueprintReadWrite)
	class USWH_Clip* CurrCombo = nullptr;

	int32 Priority;
	//��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FKey> ActionKeys;
	//��������(�����)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESWH_FInputDirection AnotherKey;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bHold;

public:
	class USWH_Clip* CreateTree(class USWH_ComboClip* ComboClip);
	void Init_Tree(class USWH_ComboTree* FirstComboData);

	void CheckComboKey(struct FKey key);
	//����ƥ��������ͷ���
	bool IsCurrentComboTree(struct FKey key, ESWH_FInputDirection DirectInput);
	bool IsHoldComboTree(struct FKey key);

	class USWH_Clip* ProcessNextCombo(ESWH_FInputDirection DirectInput);
	class USWH_Clip* ProcessBranchCombo(ESWH_FInputDirection DirectInput);
};
