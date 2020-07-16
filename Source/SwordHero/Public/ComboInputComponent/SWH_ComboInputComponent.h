// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputCoreTypes.h"
#include "../Types/SWH_Types.h"
#include "SWH_ComboInputComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SWORDHERO_API USWH_ComboInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USWH_ComboInputComponent();
	void Init(class ACharacter* owner);
	UPROPERTY()
	class USWH_Tree* ComboTree;
	UPROPERTY()
	class USWH_Tree* HoldComboTree;
	UPROPERTY()
	TArray<class USWH_Tree*> ComboTrees;
	UPROPERTY()
	TArray<class USWH_Tree*> HoldComboTrees;

	//���������ӵ����
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* SkillOwner;

	UPROPERTY(BlueprintReadOnly)
	class ASWH_BaseWeaponClass* CurrWeapon;

	UPROPERTY()
	bool HasInput;
	UPROPERTY()
	bool IsKeyHold;
	UPROPERTY()
	float KeyHoldTime;
	UPROPERTY()
	FKey CurrKey;
	UPROPERTY()
	bool AllowHoldAgain;
	UPROPERTY()
	bool Attacked;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ConstructComboTree();

	class ASWH_MotionActor* NewSkillMotion;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//��������
	void CheckInputKey(struct FKey key);
	void Input(struct FKey key, ESWH_FInputDirection DirectInput);
	void ProcessHoldKeyInput();
	void KeyReleased(FKey key, ESWH_FInputDirection DirectInput);

	//����֪ͨ����
	UFUNCTION(BlueprintCallable)
	void ResetCombo();
	UFUNCTION(BlueprintCallable)
	void AllowNextAttack();
	UFUNCTION(BlueprintCallable)
	void BanNextAttack();
	//���������ʱҪ���� Combotree->CurrCombo��״̬
	UFUNCTION(BlueprintCallable)
	void Interrupted();
	UFUNCTION(BlueprintCallable)
	void AllowNextHoldLevel();
	UFUNCTION(BlueprintCallable)
	void ResetHoldLevel();
};
