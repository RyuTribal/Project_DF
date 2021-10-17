// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DF_Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Math/UnrealMathUtility.h"
// Sets default values
ADF_Character::ADF_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init the capsule by setting the radius and half height of it
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);


	DefaultDodge = CreateDefaultSubobject<UAnimMontage>(TEXT("DefaultDodge"));

	// Remove the mouse restrictions on the camera (mouse moves camera not the character)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	// How far he jumps
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	// Sets the spring to the arm component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	CameraBoom->TargetArmLength = 300.0f; // The length of which the camera is from the player
	CameraBoom->bUsePawnControlRotation = true; // Mouse moves the arm that is attached to camera

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false; // Mouse does not move the actual camera

	CanMove = true;
	IsDodging = false;
	CanDodge = true;
	IsMoving = false;

	DodgeDistance = 2500.0f;

	DodgeDelay = 0.2f;

	DodgeCooldown = 0.1f;
	CanEnterIdle = true;
	JogSpeed = 600.f;
	SprintSpeed = 1000.f;
	IsRunning = false;
	IsEquipped = false;
	IsSheathing = false;
	CurrentAttack = 0;
}

// Called when the game starts or when spawned
void ADF_Character::BeginPlay()
{
	Super::BeginPlay();
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AWeaponBase* PlayerWeapon = GetWorld()->SpawnActor<AWeaponBase>(Weapon, Location, Rotation, SpawnInfo);
	PlayerWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("greatsword-sheathe"));
	WeaponPtr = PlayerWeapon;
	
}

// Called every frame
void ADF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADF_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// For camera movement
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// These axis commands are always fired at tick. Very important to remember
	PlayerInputComponent->BindAxis("MoveForward", this, &ADF_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADF_Character::MoveRight);

	// different inputs
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ADF_Character::Dodge);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADF_Character::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADF_Character::Jog);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ADF_Character::HandleEquip);
	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &ADF_Character::LightAttack);

}

void ADF_Character::MoveForward(float Axis)
{
	if(CanMove)
	{
		HandleChangeMovement();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector FDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(FDirection, Axis);
	}
}

void ADF_Character::MoveRight(float Axis)
{
	if (CanMove)
	{
		HandleChangeMovement();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RDirection, Axis);
		
	}
}

void ADF_Character::HandleChangeMovement()
{
	UCharacterMovementComponent* cMove = GetCharacterMovement();
	if (cMove->Velocity.Size() == 0.f) //If the character is still
	{
		IsMoving = false;
	}
	else
	{
		IsMoving = true;
	}
}

void ADF_Character::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	IsRunning = true;
}

void ADF_Character::Jog()
{
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	IsRunning = false;
}

void ADF_Character::HandleEquip()
{
	/*
	 * Animations are taken from the weapon
	 */
	UAnimInstance* Animations = GetMesh()->GetAnimInstance();
	if(IsEquipped && WeaponPtr)
	{
		if(!IsSheathing)
		{
			IsEquipped = false;
			IsSheathing = true;
			Animations->Montage_Play(WeaponPtr->Sheathe, 1.f);
			FOnMontageEnded CompleteDelegate;
			CompleteDelegate.BindUObject(this, &ADF_Character::OnEquipInterrupt);
			Animations->Montage_SetEndDelegate(CompleteDelegate, WeaponPtr->Sheathe);
		}
		
	}
	else
	{
		if(!IsSheathing)
		{
			IsEquipped = true;
			IsSheathing = true;
			EquippedWeapon = WeaponPtr->id;
			Animations->Montage_Play(WeaponPtr->UnSheathe, 1.f);
			FOnMontageEnded CompleteDelegate;
			CompleteDelegate.BindUObject(this, &ADF_Character::OnEquipInterrupt);
			Animations->Montage_SetEndDelegate(CompleteDelegate, WeaponPtr->UnSheathe);
		}
		
	}
}

void ADF_Character::OnEquipInterrupt(UAnimMontage* animMontage, bool bInterrupted)
{
	if(IsEquipped && WeaponPtr)
	{
		WeaponPtr->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("right_hand_equip"));
	}
	else
	{
		WeaponPtr->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("greatsword-sheathe"));
	}
	IsSheathing = false;
}

void ADF_Character::Dodge()
{
	UCharacterMovementComponent* cMove = GetCharacterMovement(); // Gets the character movement so that we can check if falling or the velocity ect
	if (CanDodge && !cMove->IsFalling()) {	// Don't wanna be able to dodge when falling
		DefaultFriction = cMove->BrakingFrictionFactor;	
		cMove->BrakingFrictionFactor = 0.f; //Removes friction since it messes with how far the character can be launched
		LaunchCharacter(FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0.f).GetSafeNormal() * DodgeDistance, true, true);
		IsDodging = true;
		CanMove = false;
		CanDodge = false;
		GetWorldTimerManager().SetTimer(UnusedDodgeHandle, this, &ADF_Character::StopDodge, DodgeDelay, false); //A timer to delay movement and make sure the dodge is executed
	}
}

void ADF_Character::StopDodge()
{

	GetCharacterMovement()->StopMovementImmediately(); // This is more of a safety meassure so that no movement is performed before the dodge is complete
	IsDodging = false;
	CanMove = true;
	GetCharacterMovement()->BrakingFrictionFactor = DefaultFriction; // Gives friction back to the character
	GetWorldTimerManager().SetTimer(UnusedDodgeHandle, this, &ADF_Character::ResetDodge, DodgeCooldown, false); // make the dodge have a cool down so people can't spam it
	
}

void ADF_Character::ResetDodge()
{
	CanDodge = true;
	GetWorld()->GetTimerManager().ClearTimer(UnusedDodgeHandle);
}

void ADF_Character::LightAttack()
{
	UAnimInstance* Animations = GetMesh()->GetAnimInstance();
	if(!IsEquipped)
	{
		IsEquipped = true;
		WeaponPtr->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("right_hand_equip"));
		
	}
	if(!Animations->IsAnyMontagePlaying())
	{
		IsAttacking = true;
		CurrentAttack = 1;
		Animations->Montage_Play(WeaponPtr->AttackCombo, 1.f);
		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &ADF_Character::OnAttackCompleting);
		Animations->Montage_SetEndDelegate(BlendOutDelegate, WeaponPtr->AttackCombo);
	}
	else
	{
		if(Animations->Montage_IsPlaying(WeaponPtr->AttackCombo))
		{
			FString CurrentSectionPlaying = Animations->Montage_GetCurrentSection(WeaponPtr->AttackCombo).ToString();
			FString ReferenceSection = TEXT("ComboWindow_");
			ReferenceSection.AppendInt(CurrentAttack);
			if(CurrentSectionPlaying.Equals(ReferenceSection))
			{
				FString NextSection = TEXT("Attack_");
				NextSection.AppendInt(CurrentAttack+1);
				Animations->Montage_JumpToSection(FName(NextSection), Animations->GetCurrentActiveMontage());
				CurrentAttack = CurrentAttack + 1;
			}

		}
	}
}

void ADF_Character::OnAttackCompleting(UAnimMontage* animMontage, bool bInterrupted)
{
	IsAttacking = false;
	CurrentAttack = 0;
}



