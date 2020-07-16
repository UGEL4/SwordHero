// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/CustomNotify/SWH_WeaponTraceNotifyState.h"
#include "../../Public/Weapons/SWH_BaseWeaponClass.h"
#include "../../Public/Hero1.h"
#include "../../SwordHero.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"

void USWH_WeaponTraceNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	if (Player)//检测是否报空
	{
		for (int i = 0; i < Weapon->BoxTraceSocketData.Num(); i++)
		{
			//射线检测
			UKismetSystemLibrary::BoxTraceMulti(
				Player->GetWorld(),
				LastLocations[i], Weapon->GetRootComponent()->GetSocketLocation(Weapon->BoxTraceSocketData[i].TraceSocketName),
				Weapon->BoxTraceSocketData[i].HalfSize,
				Weapon->GetRootComponent()->GetComponentRotation(),
				UEngineTypes::ConvertToTraceType(COLLECTION_PLAYERATTACK),
				false, ActorsToIgnore, EDrawDebugTrace::None,
				HitResults, true);

			for (int i = 0; i < HitResults.Num(); i++)
			{
				AActor*HitActor = HitResults[i].GetActor();//获取本次射线击中的Actor//
				if (!HitActors.Contains(HitActor))//查询数组中是否有本次击中的Actor，如果没有则添加进数组并调用自带伤害函数，防止一次通知内多次击中的情况//
				{
					HitActors.Add(HitActor);
					Weapon->SetHitBoneMap(HitResults[i].GetActor(), HitResults[i].BoneName);

					UGameplayStatics::ApplyDamage(HitActor, Weapon->DamageValue, EventInstigator, Player, DamageTypeClass);
					Weapon->PlayHitEffect(&HitResults[i]);
				}
			}
			
		}
		//一次Tick过后更新当前插槽的位置变量，下一次再与存储的变量做差值//
		for (int i = 0; i < Weapon->GetBoxTraceSocketData().Num(); i++)
		{
			LastLocations[i] = Weapon->GetRootComponent()->GetSocketLocation(Weapon->BoxTraceSocketData[i].TraceSocketName);
		}
	}
}

void USWH_WeaponTraceNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	HitActors.Empty();
	LastLocations.Empty();
}

void USWH_WeaponTraceNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Player = Cast<AHero1>(MeshComp->GetOwner());
	if (Player)
	{
		Weapon = Player->CurrWeapon;
		ActorsToIgnore = { MeshComp->GetOwner() };
		if (Weapon->BoxTraceSocketData.Num() > 0)
		{
			for (auto& BoxTraceData : Weapon->BoxTraceSocketData)
			{
				LastLocations.Add(Weapon->GetRootComponent()->GetSocketLocation(BoxTraceData.TraceSocketName));
			}
		}
	}
}
