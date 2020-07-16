// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwinSword.generated.h"

UCLASS()
class SWORDHERO_API ATwinSword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATwinSword();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComp")
	class UStaticMeshComponent* MeshComp;
	
	
};
