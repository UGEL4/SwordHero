// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SWH_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SWORDHERO_API USWH_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//在 gameinstance 中的 init()方法中初始化
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "AutoLoadPrimary")
	TArray<FPrimaryAssetType> AutoLoadTypes;

	virtual void Init() override;
	//读取AutoLoadTypes中的内容
	void AutoLoadDataAssets();

	UFUNCTION(BlueprintCallable)
	const TArray<FPrimaryAssetType>& GetLoadTypes() const { return AutoLoadTypes; }
};
