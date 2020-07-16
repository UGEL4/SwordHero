// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hero1.generated.h"


class ASingleSword;
class ASWH_BaseWeaponClass;
class USWH_HealthComponent;
UCLASS()
class SWORDHERO_API AHero1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero1();

	void MoveForword(float val);
	void MoveRight(float val);

	void JumpStart();
	void JumpEnd();

	//手柄配置
	void TurnAtRate(float val);
	void LookUpAtRate(float val);

	void AttackInput(FKey key);
	void PerformAttack(FKey key);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//摄像机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComp;
	//弹簧臂
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArmComp;

	/*UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<ASingleSword> StarterWeaponClass;*/
public:

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<ASWH_BaseWeaponClass> StarterWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	ASWH_BaseWeaponClass* CurrWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Properties | Health Component")
	USWH_HealthComponent* HealthComp;

	UPROPERTY(BlueprintReadWrite)
	TArray<FHitResult> HitResults;

	UPROPERTY()
		TArray<AActor*> ActorsToIgnore;
protected:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo Input Component", meta = (AllowPrivateAccess = "true"))
	USWH_ComboInputComponent* ComboInputComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo Input Component", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USWH_ComboInputComponent> ComboInputComponentClass;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	FVector2D Axis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Action")
	bool IsDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Action")
	bool CanDodge;

	UPROPERTY(BlueprintReadWrite, Category = "Character Action")
	bool CanDodgeAgain;

	//闪避的距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Action")
	float DodgeLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Action")
	bool Jumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Action")
	bool CanJumpAgain;

	//用于判断是否使输入轴有效（在闪避的时候不应该能够转向）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Action")
	bool CanMove;

	UPROPERTY(BlueprintReadWrite, Category = "Character Action")
	bool FMoving;

	UPROPERTY(BlueprintReadWrite, Category = "Character Action")
	bool RMoving;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	bool IsEquipWeapon;

	UPROPERTY(BlueprintReadWrite)
	bool bDied;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//防御功能
	UFUNCTION(BlueprintCallable, Category = "Customer Input", meta = (Keywords = "Defense"))
	void AddDefense(float val);

	UFUNCTION(BlueprintCallable, Category = "Customer Input", meta = (Keywords = "Dodge"))
	void AddDodge();

	UFUNCTION(BlueprintCallable, Category = "Customer Input", meta = (Keywords = "StopDodge"))
	void StopDodge();

	void EquipWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_EquipWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_AutoAimEnemy();

	UFUNCTION()
	void OnHealthChanged(USWH_HealthComponent* HealthComponent,
			float Health, float HealthDelta, const class UDamageType* DamageType,
			class AController* InstigatedBy, class AActor* DamageCauser);

	void AutoAimTrace();
};
