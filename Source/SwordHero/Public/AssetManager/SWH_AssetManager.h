// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SWH_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SWORDHERO_API USWH_AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static const FPrimaryAssetType MotionType;
	static const FPrimaryAssetType ComboType;

	/** Returns the current AssetManager object */
	static USWH_AssetManager& Get();
};
