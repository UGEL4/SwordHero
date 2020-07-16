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
		//��ȡ��ǰtype�µ������ʲ���ID�����統ǰ�������µĸ��ּ���ID
		FPrimaryAssetType CurrType = type;
		TArray<FPrimaryAssetId> AssetIDs;
		if (manage.GetPrimaryAssetIdList(CurrType, AssetIDs))
		{
			manage.LoadPrimaryAssets(AssetIDs, TArray<FName>(), FStreamableDelegate(), 0);
		}
	}
}
