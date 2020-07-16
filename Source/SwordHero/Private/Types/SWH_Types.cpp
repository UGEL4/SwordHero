// Fill out your copyright notice in the Description page of Project Settings.

#include "SWH_Types.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void FSWH_ComposeKeyStruct::CheckKey(FKey key)
{
	if (ComposeKeys.Num() > 0)
	{
		if (ComposeKeys.Num() > 1)
		{
			for (auto& _key : ComposeKeys)
			{
				if (key == _key)
				{
					continue;
				}
				Okay = UGameplayStatics::GetPlayerController(GWorld, 0)->IsInputKeyDown(_key);
			}
		}
		else
		{
			Okay = (key == ComposeKeys[0]);
		}
	}
}