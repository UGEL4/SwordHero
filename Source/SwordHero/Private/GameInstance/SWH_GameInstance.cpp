// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/GameInstance/SWH_GameInstance.h"
#include "../../Public/AssetManager/SWH_AssetManager.h"

void USWH_GameInstance::Init()
{
	Super::Init();
	AutoLoadDataAssets();
}

void USWH_GameInstance::AutoLoadDataAssets()
{
	USWH_AssetManager& manage = USWH_AssetManager::Get();
	for (auto& type : AutoLoadTypes)
	{
		//读取当前type下的所有资产的ID，例如当前技能类下的各种技能ID
		FPrimaryAssetType CurrType = type;
		TArray<FPrimaryAssetId> AssetIDs;
		if (manage.GetPrimaryAssetIdList(CurrType, AssetIDs))
		{
			manage.LoadPrimaryAssets(AssetIDs, TArray<FName>(), FStreamableDelegate(), 0);
		}
	}
}
