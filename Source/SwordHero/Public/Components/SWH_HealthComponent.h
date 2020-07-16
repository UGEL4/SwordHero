// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Types/SWH_Types.h"
#include "SWH_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, USWH_HealthComponent*, HealthComponent,
float, health, float, HealthDelta, const class UDamageType*, DamageType, 
class AController*, InstigatedBy, class AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SWORDHERO_API USWH_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USWH_HealthComponent();

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSWH_PropertyValue HealthData;

	UFUNCTION(BlueprintPure)
	FORCEINLINE FSWH_PropertyValue& GetHealthData() { return HealthData; }

	UFUNCTION()
	virtual void UpdateHealthUI();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateHealthUI();

	UFUNCTION(BlueprintCallable)
	void SetHealthValue(float value, bool bUpdateUI);

	UFUNCTION(BlueprintCallable)
	void ModifyHealthValue(float value, bool bUpdateUI);

	UPROPERTY(VisibleAnywhere,BlueprintAssignable, Category = "Events")
	FOnHealthChangeSignature OnHealthChanged;
};
