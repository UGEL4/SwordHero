// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SWH_Items.generated.h"

/**
 *	�����ʲ����࣬ʹ����������ͬ�������ʲ���
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
