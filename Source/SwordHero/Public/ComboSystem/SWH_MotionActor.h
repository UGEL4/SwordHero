// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWH_MotionActor.generated.h"

UCLASS()
class SWORDHERO_API ASWH_MotionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWH_MotionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void Perform(class ACharacter* SkillOwner, class USWH_Clip* ComboClip);

	UFUNCTION()
	virtual void ProcessSkill(class ACharacter* SkillOwner, class USWH_Clip* ComboClip);

	//在蓝图中实现处理技能的逻辑，以便在c++中调用它
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ProcessSkill(class ACharacter* SkillOwner, class USWH_Clip* ComboClip);
};
