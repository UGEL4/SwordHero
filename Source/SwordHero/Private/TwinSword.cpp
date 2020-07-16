// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinSword.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATwinSword::ATwinSword()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}
