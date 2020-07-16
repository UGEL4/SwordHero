// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/ComboSystem/SWH_Clip.h"
#include "../../Public/Items/SWH_ComboTree.h"
#include "../../Public/Items/SWH_ComboClip.h"

void USWH_Clip::ConstructComposeKeys()
{
	if (ComboClipData)
	{
		if (ComboClipData->AttackMotionData.NextAttackMotionKeys.Num() > 0)
		{
			for (auto& key : ComboClipData->AttackMotionData.NextAttackMotionKeys)
			{
				NextComboComposeKeyStruct.ComposeKeys.Add(key);
			}
		}
		if (ComboClipData->AttackMotionData.BranchAttackMotionKeys.Num() > 0)
		{
			for (auto& key : ComboClipData->AttackMotionData.BranchAttackMotionKeys)
			{
				BranchComboComposeKeyStruct.ComposeKeys.Add(key);
			}
		}
	}
}

void USWH_Clip::ConstructFirstComboComposeKeys(class USWH_ComboTree* FirstComboData)
{
	if (FirstComboData->ActionKeys.Num() > 0)
	{
		for (auto& key : FirstComboData->ActionKeys)
		{
			NextComboComposeKeyStruct.ComposeKeys.Add(key);
		}

	}
}
