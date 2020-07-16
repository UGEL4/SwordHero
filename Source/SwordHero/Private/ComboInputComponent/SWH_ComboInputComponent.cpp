// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/ComboInputComponent/SWH_ComboInputComponent.h"
#include "../../Public/ComboSystem/SWH_MotionActor.h"
#include "../../Public/ComboSystem/SWH_Tree.h"
#include "../../Public/ComboSystem/SWH_Clip.h"
#include "../../Public/Items/SWH_ComboTree.h"
#include "../../Public/Items/SWH_ComboClip.h"
#include "../../Public/AssetManager/SWH_AssetManager.h"
#include "../../Public/Weapons/SWH_BaseWeaponClass.h"
#include "GameFrameWork/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USWH_ComboInputComponent::USWH_ComboInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ComboTree = nullptr;
	HoldComboTree = nullptr;
	NewSkillMotion = nullptr;
	HasInput = false;
	IsKeyHold = false;
	KeyHoldTime = 0.f;
	AllowHoldAgain = true;
	Attacked = false;
}

void USWH_ComboInputComponent::Init(ACharacter* owner)
{
	//放BeginPlay中初始化会出现owner为nullptr的问题
	check(GetOwner());
	CurrWeapon = Cast<ASWH_BaseWeaponClass>(GetOwner());
	SkillOwner = owner;
	ConstructComboTree();
	if (ComboTrees.Num() > 0)
	{
		UClass* SkillMotionClass = ComboTrees[0]->ComboClipHead->ComboClipData->Skill.Get();
		NewSkillMotion = GetWorld()->SpawnActor<ASWH_MotionActor>(SkillMotionClass, SkillOwner->GetTransform());
	}
}

// Called when the game starts
void USWH_ComboInputComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void USWH_ComboInputComponent::ConstructComboTree()
{
	USWH_AssetManager& manager = USWH_AssetManager::Get();
	TArray<FPrimaryAssetId> AssetId;
	manager.GetPrimaryAssetIdList(USWH_AssetManager::ComboType, AssetId);
	for (auto& ID : AssetId)
	{
		USWH_ComboTree* tree = manager.GetPrimaryAssetObject<USWH_ComboTree>(ID);
		if (tree && tree->SkillTreeOwner && SkillOwner->IsA(tree->SkillTreeOwner.Get()))
		{
			USWH_Tree* NewTree = NewObject<USWH_Tree>(this);
			//构造头结点
			NewTree->ComboClipHead = NewObject<USWH_Clip>(this);
			NewTree->ComboClipHead->ComboClipData = tree->FirstCombClip;
			NewTree->Init_Tree(tree);

			NewTree->ComboClipHead->NextClip = NewTree->CreateTree(tree->FirstCombClip);
			if (NewTree->ComboClipHead->NextClip)
			{
				NewTree->CurrCombo = NewTree->ComboClipHead;
			}
			if (tree->bHold)
			{
				HoldComboTrees.Add(NewTree);
			}
			else
			{
				ComboTrees.Add(NewTree);
			}
		}
	}
	//对连击树进行排序
	ComboTrees.Sort([](const USWH_Tree& a, const USWH_Tree& b)
	{
		return a.Priority < b.Priority;
	});
	HoldComboTrees.Sort([](const USWH_Tree& a, const USWH_Tree& b)
	{
		return a.Priority < b.Priority;
	});
}

// Called every frame
void USWH_ComboInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (HasInput)
	{
		KeyHoldTime = UGameplayStatics::GetPlayerController(GWorld, 0)->GetInputKeyTimeDown(CurrKey);
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, UKismetStringLibrary::Conv_FloatToString(KeyHoldTime));
		if (KeyHoldTime > 0.20f && KeyHoldTime < 0.22f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("HOLD"));
			ProcessHoldKeyInput();
		}
	}
}

void USWH_ComboInputComponent::CheckInputKey(struct FKey key)
{
	HasInput = true;
	CurrKey = key;
}

void USWH_ComboInputComponent::Input(struct FKey key, ESWH_FInputDirection DirectInput)
{
	if (ComboTrees.Num() > 0)
	{

		if (ComboTree == nullptr)
		{
			//找出连击树
			for (USWH_Tree* CurrTree : ComboTrees)
			{
				bool bFound = CurrTree->IsCurrentComboTree(key, DirectInput);
				if (bFound)
				{
					ComboTree = CurrTree;
					break;
				}
			}
		}

		//找到了连击树
		if (ComboTree)
		{
			//处理连击
			USWH_Clip* combo = nullptr;
			ComboTree->CheckComboKey(key);
			if (ComboTree->CurrCombo && ComboTree->CurrCombo->NextComboComposeKeyStruct.Okay)
			{
				ComboTree->CurrCombo->NextComboComposeKeyStruct.Okay = false;
				AllowHoldAgain = false;
				Attacked = true;
				combo = ComboTree->ProcessNextCombo(DirectInput);
			}
			else if (ComboTree->CurrCombo && ComboTree->CurrCombo->BranchComboComposeKeyStruct.Okay)
			{
				Attacked = true;
				AllowHoldAgain = false;
				ComboTree->CurrCombo->BranchComboComposeKeyStruct.Okay = false;
				combo = ComboTree->ProcessBranchCombo(DirectInput);
			}
			if (combo && NewSkillMotion)
			{
				if (CurrWeapon)
				{
					CurrWeapon->DamageValue = combo->ComboClipData->AttackMotionData.AttackDamageAmount;
				}
				NewSkillMotion->Perform(SkillOwner, combo);
			}
		}
	}
}

void USWH_ComboInputComponent::ProcessHoldKeyInput()
{
	if (HoldComboTrees.Num() > 0 && AllowHoldAgain)
	{
		for (auto& CurrHoldTree : HoldComboTrees)
		{
			bool IsHoldTree = CurrHoldTree->IsHoldComboTree(CurrKey);
			if (IsHoldTree)
			{
				HoldComboTree = CurrHoldTree;
				break;
			}
		}
		if (HoldComboTree)
		{
			//处理蓄力动作
			//USWH_Clip* combo = nullptr;
			HoldComboTree->CurrCombo->AllowNextAttack = false;
			AllowHoldAgain = false;
			HoldComboTree->CurrCombo = HoldComboTree->CurrCombo->NextClip;
			//接下来就是通过动画通知来改变蓄力阶段,当按键松开后就释放技能
			if (NewSkillMotion)
			{
				NewSkillMotion->Perform(SkillOwner, HoldComboTree->CurrCombo);
			}
			return;
		}
	}
	//没找到蓄力连击树就执行普通连击
	else
	{
		if (!Attacked && AllowHoldAgain)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("NO HOLD"));
			//Attacked = true;
			HasInput = false;
			Input(CurrKey, ESWH_FInputDirection::ENone);
		}
	}
}

void USWH_ComboInputComponent::KeyReleased(FKey key, ESWH_FInputDirection DirectInput)
{
	if (HoldComboTree == nullptr)
	{
		if (!Attacked)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("RELEASED NO HOLD"));
			HasInput = false;
			Input(key, DirectInput);
		}
	}
	else
	{
		//释放蓄力技能
		USWH_Clip* combo = nullptr;
		HasInput = false;
		AllowHoldAgain = false;
		if (HoldComboTree)
		{
			HoldComboTree->CurrCombo->AllowNextAttack = false;
			if (HoldComboTree->CurrCombo->BranchClip)
			{
				combo = HoldComboTree->CurrCombo->BranchClip;
				if (combo && NewSkillMotion)
				{
					if (CurrWeapon)
					{
						CurrWeapon->DamageValue = combo->ComboClipData->AttackMotionData.AttackDamageAmount;
					}
					NewSkillMotion->Perform(SkillOwner, combo);
				}
			}
			HoldComboTree->CurrCombo = HoldComboTree->ComboClipHead;
		}
	}
}

void USWH_ComboInputComponent::ResetCombo()
{
	AllowHoldAgain = true;
	Attacked = false;
	ComboTree->CurrCombo->AllowNextAttack = false;
	ComboTree->CurrCombo = ComboTree->ComboClipHead;
	ComboTree->ComboClipHead->AllowNextAttack = true;
	ComboTree = nullptr;
}

void USWH_ComboInputComponent::AllowNextAttack()
{
	Attacked = false;
	ComboTree->CurrCombo->AllowNextAttack = true;
}

void USWH_ComboInputComponent::BanNextAttack()
{
	ComboTree->CurrCombo->AllowNextAttack = false;
}

void USWH_ComboInputComponent::Interrupted()
{
	AllowHoldAgain = true;
	ComboTree->CurrCombo->AllowNextAttack = false;
	ComboTree->CurrCombo = ComboTree->ComboClipHead;
	ComboTree->ComboClipHead->AllowNextAttack = true;
	ComboTree = nullptr;
}

void USWH_ComboInputComponent::AllowNextHoldLevel()
{
	if (HoldComboTree->CurrCombo && HoldComboTree->CurrCombo->NextClip)
	{
		HoldComboTree->CurrCombo->AllowNextAttack = false;
		HoldComboTree->CurrCombo = HoldComboTree->CurrCombo->NextClip;
		NewSkillMotion->Perform(SkillOwner, HoldComboTree->CurrCombo);
	}
}

void USWH_ComboInputComponent::ResetHoldLevel()
{
	HoldComboTree->ComboClipHead->AllowNextAttack = true;
	AllowHoldAgain = true;
	HoldComboTree = nullptr;
}

