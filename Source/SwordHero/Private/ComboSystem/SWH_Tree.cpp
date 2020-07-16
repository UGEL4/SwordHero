// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/ComboSystem/SWH_Tree.h"
#include "../../Public/ComboSystem/SWH_Clip.h"
#include "../../Public/Items/SWH_ComboClip.h"
#include "../../Public/Items/SWH_ComboTree.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

class USWH_Clip* USWH_Tree::CreateTree(USWH_ComboClip* ComboClip)
{
	//前序遍历树来创建树
	USWH_Clip* Root;
	if (ComboClip == nullptr)
	{
		Root = nullptr;
	}
	else
	{
		Root = NewObject<USWH_Clip>(this);
		Root->ComboClipData = ComboClip;
		//Root->ConstructKeySM();
		Root->ConstructComposeKeys();

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, ComboClip->AttackMotionData.AttackMotionName.ToString());

		Root->NextClip = CreateTree(ComboClip->NextCombo);
		Root->BranchClip = CreateTree(ComboClip->BranchCombo);
	}

	return Root;
}

void USWH_Tree::Init_Tree(USWH_ComboTree* FirstComboData)
{
	if (FirstComboData)
	{
		if (FirstComboData->ActionKeys.Num() > 0)
		{
			for (auto& key : FirstComboData->ActionKeys)
			{
				ActionKeys.Add(key);
			}
		}
		AnotherKey = FirstComboData->AnotherKey;
		ComboClipHead->AllowNextAttack = true;
		Priority = FirstComboData->Priority;
		bHold = FirstComboData->bHold;
		ComboClipHead->ConstructFirstComboComposeKeys(FirstComboData);
	}
}

void USWH_Tree::CheckComboKey(FKey key)
{
	if (CurrCombo && CurrCombo->AllowNextAttack)
	{
		//处理组合按键匹配
		if (CurrCombo->NextComboComposeKeyStruct.ComposeKeys.Num() > 0)
		{
			CurrCombo->NextComboComposeKeyStruct.CheckKey(key);
		}
		if (CurrCombo->BranchComboComposeKeyStruct.ComposeKeys.Num() > 0)
		{
			CurrCombo->BranchComboComposeKeyStruct.CheckKey(key);
		}
	}
}

bool USWH_Tree::IsCurrentComboTree(FKey key, ESWH_FInputDirection DirectInput)
{
	bool ok = false;
	if (ActionKeys.Num() > 0)
	{
		//处理组合按键匹配
		if (ActionKeys.Num() > 1)
		{
			for (auto& _key : ActionKeys)
			{
				if (_key == key)
				{
					continue;
				}
				ok = UGameplayStatics::GetPlayerController(GWorld, 0)->IsInputKeyDown(_key);
			}
			if (AnotherKey != ESWH_FInputDirection::ENone)
			{
				if (DirectInput != AnotherKey)
				{
					ok = false;
				}
			}
		}
		else
		{
			//不是组合按键
			ok = (key == ActionKeys[0]);
			if (AnotherKey != ESWH_FInputDirection::ENone)
			{
				ok = (DirectInput == AnotherKey);
			}
		}
	}
	return ok;
}

bool USWH_Tree::IsHoldComboTree(FKey key)
{
	bool ok = false;
	if (ActionKeys.Num() > 0)
	{
		//处理组合按键匹配
		if (ActionKeys.Num() > 1)
		{
			for (auto& _key : ActionKeys)
			{
				if (_key == key)
				{
					continue;
				}
				ok = UGameplayStatics::GetPlayerController(GWorld, 0)->IsInputKeyDown(_key);
			}
		}
		else
		{
			//不是组合按键
			ok = (key == ActionKeys[0]);
		}
	}
	return ok;
}

class USWH_Clip* USWH_Tree::ProcessNextCombo(ESWH_FInputDirection DirectInput)
{
	if (CurrCombo)
	{
		if (CurrCombo->ComboClipData->AttackMotionData.NextAttackDirectionInput != ESWH_FInputDirection::ENone)
		{
			if (DirectInput == (CurrCombo->ComboClipData->AttackMotionData.NextAttackDirectionInput))
			{

				CurrCombo->AllowNextAttack = false;
				CurrCombo = CurrCombo->NextClip;
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, CurrCombo->ComboClipData->AttackMotionData.AttackMotionName.ToString());
				return CurrCombo;
			}
			else
			{
				CurrCombo->AllowNextAttack = false;
				CurrCombo = ComboClipHead;
				CurrCombo->AllowNextAttack = true;
				return nullptr;
			}

		}
		else
		{
			CurrCombo->AllowNextAttack = false;
			CurrCombo = CurrCombo->NextClip;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, CurrCombo->ComboClipData->AttackMotionData.AttackMotionName.ToString());
			return CurrCombo;
		}
	}
	return nullptr;
}

class USWH_Clip* USWH_Tree::ProcessBranchCombo(ESWH_FInputDirection DirectInput)
{
	if (CurrCombo)
	{
		if (CurrCombo->ComboClipData->AttackMotionData.BranchAttackDirectionInput != ESWH_FInputDirection::ENone)
		{
			if (DirectInput == (CurrCombo->ComboClipData->AttackMotionData.BranchAttackDirectionInput))
			{
				CurrCombo->AllowNextAttack = false;
				CurrCombo = CurrCombo->BranchClip;
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, CurrCombo->ComboClipData->AttackMotionData.AttackMotionName.ToString());
				return CurrCombo;
			}
			else
			{
				CurrCombo->AllowNextAttack = false;
				CurrCombo = ComboClipHead;
				CurrCombo->AllowNextAttack = true;
				return nullptr;
			}
		}
		else
		{
			CurrCombo->AllowNextAttack = false;
			CurrCombo = CurrCombo->BranchClip;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, CurrCombo->ComboClipData->AttackMotionData.AttackMotionName.ToString());
			return CurrCombo;
		}
	}
	return nullptr;
}
