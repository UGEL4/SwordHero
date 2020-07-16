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
	if (Player)//����Ƿ񱨿�
	{
		for (int i = 0; i < Weapon->BoxTraceSocketData.Num(); i++)
		{
			//���߼��
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
				AActor*HitActor = HitResults[i].GetActor();//��ȡ�������߻��е�Actor//
				if (!HitActors.Contains(HitActor))//��ѯ�������Ƿ��б��λ��е�Actor�����û������ӽ����鲢�����Դ��˺���������ֹһ��֪ͨ�ڶ�λ��е����//
				{
					HitActors.Add(HitActor);
					Weapon->SetHitBoneMap(HitResults[i].GetActor(), HitResults[i].BoneName);

					UGameplayStatics::ApplyDamage(HitActor, Weapon->DamageValue, EventInstigator, Player, DamageTypeClass);
					Weapon->PlayHitEffect(&HitResults[i]);
				}
			}
			
		}
		//һ��Tick������µ�ǰ��۵�λ�ñ�������һ������洢�ı�������ֵ//
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
