// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/ComboSystem/SWH_MotionActor.h"
#include "../../Public/ComboSystem/SWH_Clip.h"
#include "GameFramework/Character.h"

// Sets default values
ASWH_MotionActor::ASWH_MotionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASWH_MotionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASWH_MotionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASWH_MotionActor::Perform(class ACharacter* SkillOwner, class USWH_Clip* ComboClip)
{
	ProcessSkill(SkillOwner, ComboClip);
	BP_ProcessSkill(SkillOwner, ComboClip);
}

void ASWH_MotionActor::ProcessSkill(class ACharacter* SkillOwner, class USWH_Clip* ComboClip)
{

}