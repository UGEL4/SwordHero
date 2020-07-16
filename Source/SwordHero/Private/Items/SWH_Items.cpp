// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Items/SWH_Items.h"

FPrimaryAssetId USWH_Items::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(AssetType, GetFName());
}
