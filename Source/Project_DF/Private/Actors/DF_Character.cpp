// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DF_Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
// Sets default values
ADF_Character::ADF_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init the capsule by setting the radius and half height of it
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);


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

	DodgeDistance = 6000.0f;

	DodgeDelay = 0.1f;

}

// Called when the game starts or when spawned
void ADF_Character::BeginPlay()
{
	Super::BeginPlay();
	
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ADF_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADF_Character::MoveRight);

	// different inputs
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ADF_Character::Dodge);


}

void ADF_Character::MoveForward(float Axis)
{
	if(CanMove)
	{
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
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RDirection, Axis);
	}
}

void ADF_Character::Dodge()
{
	UCharacterMovementComponent* cMove = GetCharacterMovement(); // Gets the character movement so that we can check if falling or the velocity ect
	if (!IsDodging && !cMove->IsFalling()) {
		DefaultFriction = cMove->BrakingFrictionFactor;
		cMove->BrakingFrictionFactor = 0.f;
		LaunchCharacter(FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0.f).GetSafeNormal() * DodgeDistance, true, true);
		IsDodging = true;
		CanMove = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADF_Character::StopDodge, DodgeDelay, false);
	}
}

void ADF_Character::StopDodge()
{
	UCharacterMovementComponent* cMove = GetCharacterMovement();
	cMove->StopMovementImmediately();
	IsDodging = false;
	CanMove = true;
	cMove->BrakingFrictionFactor = DefaultFriction;
}



