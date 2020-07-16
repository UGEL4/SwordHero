// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SWH_Items.generated.h"

/**
 *	数据资产基类，使用它派生不同的数据资产类
 */
UCLASS(Abstract)
class SWORDHERO_API USWH_Items : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType AssetType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
