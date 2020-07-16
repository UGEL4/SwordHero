// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/AssetManager/SWH_AssetManager.h"

const FPrimaryAssetType USWH_AssetManager::MotionType = TEXT("MotionType");
const FPrimaryAssetType USWH_AssetManager::ComboType = TEXT("ComboType");

USWH_AssetManager& USWH_AssetManager::USWH_AssetManager::Get()
{

	USWH_AssetManager* Singleton = Cast<USWH_AssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		//UE_LOG(LogAssetManager, Fatal, TEXT("Cannot use AssetManager if no AssetManagerClassName is defined!"));
		return *NewObject<USWH_AssetManager>(); // never calls this
	}
}
