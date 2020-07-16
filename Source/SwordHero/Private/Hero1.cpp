// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/Hero1.h"
#include "../SwordHero.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Public/Weapons/SWH_BaseWeaponClass.h"
#include "Public/ComboInputComponent/SWH_ComboInputComponent.h"
#include "Public/Components/SWH_HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AHero1::AHero1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 90.0f;
	BaseLookUpRate = 90.0f;

	//旋转视角时不旋转角色
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//让角色可以根据输入方向转身
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//默认角色旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	HealthComp = CreateDefaultSubobject<USWH_HealthComponent>(TEXT("HealthComp"));


	Axis = FVector2D::ZeroVector;

	//默认不防御
	IsDefense = false;

	//闪避
	CanDodge = false;
	CanDodgeAgain = true;
	DodgeLength = 3000.0f;

	Jumping = false;
	CanJumpAgain = true;
	CanMove = true;
	FMoving = false;
	RMoving = false;
	IsEquipWeapon = false;
	bDied = false;
}

void AHero1::MoveForword(float val)
{
	if ((Controller != NULL) && (val != 0.0f) && !IsDefense && CanMove)
	{
		FMoving = true;
		Axis.Y = val;
		const FRotator rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, rotation.Yaw, 0.0f);
		const FVector direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, val);
	}
	else
	{
		Axis.Y = 0.0f;
		FMoving = false;
	}
}

void AHero1::MoveRight(float val)
{
	if ((Controller != NULL) && (val != 0.0f) && !IsDefense && CanMove)
	{
		RMoving = true;
		Axis.X = val;
		const FRotator rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, rotation.Yaw, 0.0f);
		const FVector direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, val);	
	}
	else
	{
		Axis.X = 0.0f;
		RMoving = false;
	}
}

void AHero1::JumpStart()
{
	if (!CanDodge)
	{
		//当跳跃动画本身拥有向前位移时可以用下面的方法来旋转跳跃方向
		/*FVector JumpDirection = GetCharacterMovement()->GetLastInputVector();
		if (JumpDirection != FVector::ZeroVector)
		{
			FRotator Rotator = UKismetMathLibrary::Conv_VectorToRotator(JumpDirection);
			SetActorRotation(Rotator);
		}*/
		
		Jumping = true;
		Jump();
		CanJumpAgain = false;
	}
	
}

void AHero1::JumpEnd()
{
	Jumping = false;
	StopJumping();
}

void AHero1::TurnAtRate(float val)
{
	AddControllerYawInput(val * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void AHero1::LookUpAtRate(float val)
{
	AddControllerPitchInput(val * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
}

void AHero1::AttackInput(FKey key)
{
	if (CurrWeapon)
	{
		if (!IsEquipWeapon)
		{
			EquipWeapon();
		}
		CurrWeapon->CheckInput(key);
	}
}

void AHero1::PerformAttack(FKey key)
{
	if (CurrWeapon)
	{
		FVector F = GetCapsuleComponent()->GetForwardVector();
		FVector LastInput = GetCharacterMovement()->GetLastInputVector();
		float s = UKismetMathLibrary::Dot_VectorVector(F, LastInput);
		ESWH_FInputDirection direction;
		if (s > 0)
		{
			direction = ESWH_FInputDirection::EForward;
		}
		else if (s < 0)
		{
			direction = ESWH_FInputDirection::EBack;
		}
		else
		{
			direction = ESWH_FInputDirection::ENone;
		}

		if (!IsEquipWeapon)
		{
			EquipWeapon();
		}
		//AutoAimTrace();
		BP_AutoAimEnemy();
		CurrWeapon->Attack(key, direction);
	}
}

// Called when the game starts or when spawned
void AHero1::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (StarterWeaponClass)
	{
		ASWH_BaseWeaponClass* Temp = NewObject<ASWH_BaseWeaponClass>(this, StarterWeaponClass);

		CurrWeapon = GetWorld()->SpawnActor<ASWH_BaseWeaponClass>(StarterWeaponClass, 
			Temp->GetRootComponent()->GetSocketLocation(Temp->RootSocketName), 
			Temp->GetRootComponent()->GetSocketRotation(Temp->RootSocketName), SpawnParameters);

		if (CurrWeapon)
		{
			CurrWeapon->SetWeaponOwner(this);
			CurrWeapon->SetOwner(this);
			CurrWeapon->InitComboInputComponent(CurrWeapon->WeaponOwner);
			CurrWeapon->AttachToComponent((USceneComponent*)GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CurrWeapon->RootSocketName);
		}
	}

	HealthComp->OnHealthChanged.AddDynamic(this, &AHero1::OnHealthChanged);
}

void AHero1::AddDefense(float val)
{
	if (val > 0.0f)
	{
		IsDefense = true;
	}
	else
	{
		IsDefense = false;
	}
}

void AHero1::AddDodge()
{
	//空中不能闪避
	if (!GetMovementComponent()->IsFalling() && CanDodgeAgain)
 	{
		//GetMesh()->GetAnimInstance()->SetRootMotionMode(ERootMotionMode::RootMotionFromEverything);
		CanDodgeAgain = false;
		CanDodge = true;
		CanMove = false;
		//产生闪避
		FVector DodgeDirection = GetCharacterMovement()->GetLastInputVector();
		if (DodgeDirection != FVector::ZeroVector)
		{
			FRotator Rotator = UKismetMathLibrary::Conv_VectorToRotator(DodgeDirection);
			SetActorRotation(Rotator);
		}
		//LaunchCharacter(GetActorForwardVector() * DodgeLength, true, false);
	}
}

void AHero1::StopDodge()
{
	//CanDodge = false;
	//GetMesh()->GetAnimInstance()->SetRootMotionMode(ERootMotionMode::RootMotionFromMontagesOnly);
}

void AHero1::EquipWeapon()
{
	BP_EquipWeapon();
}

void AHero1::OnHealthChanged(USWH_HealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser)
{
	if (Health <= 0 && !bDied)
	{
		bDied = true;
		//GetMovementComponent()->StopMovementImmediately();
		GetCharacterMovement()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
		CurrWeapon->SetLifeSpan(5.f);
		SetLifeSpan(5.f);
	}
}

void AHero1::AutoAimTrace()
{
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 250.f,
		UEngineTypes::ConvertToTraceType(AUTO_AIM_TRACE), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults,
		true);
}

// Called every frame
void AHero1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHero1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//绑定按键
	PlayerInputComponent->BindAxis("MoveForward", this, &AHero1::MoveForword);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHero1::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AHero1::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AHero1::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHero1::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHero1::JumpEnd);

	PlayerInputComponent->BindAxis("TurnRate", this, &AHero1::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHero1::LookUpAtRate);

	//防御
	PlayerInputComponent->BindAxis("Defense", this, &AHero1::AddDefense);

	//闪避
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AHero1::AddDodge);
	PlayerInputComponent->BindAction("Dodge", IE_Released, this, &AHero1::StopDodge);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHero1::AttackInput);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AHero1::PerformAttack);
}
