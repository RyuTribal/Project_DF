// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "Actors/Component/TargetSystem.h"
#include "WeaponBase.h"
#include "DF_Character.generated.h"


class UCurveFloat;

UCLASS()
class PROJECT_DF_API ADF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADF_Character();

	// The spring arm so that the camera doesn't clip through the wall
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;
	// The actual camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* FollowCamera;
	UFUNCTION()
		void MoveForward(float Axis);
	UFUNCTION()
		void MoveRight(float Axis);
	UFUNCTION()
		void Dodge();
	UFUNCTION()
		void StopDodge();
	UFUNCTION()
		void ResetDodge();
	UFUNCTION()
		void HandleChangeMovement(); //Handles different variables that are affected by change in character movement
	UFUNCTION()
		void Sprint();
	UFUNCTION()
		void Jog();
	UFUNCTION()
		void HandleEquip();
	UFUNCTION()
		void OnEquipInterrupt(UAnimMontage* animMontage, bool bInterrupted);
	UFUNCTION()
		void OnAttackCompleting(UAnimMontage* animMontage, bool bInterrupted);
	UFUNCTION()
		void LightAttack();
	UFUNCTION()
		void TargetLockPressed();
	UFUNCTION()
		void StartAttack();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetLocking")
		bool IsLocked;
	UPROPERTY()
		bool CanTrack;
	UFUNCTION()
		virtual FRotator GetDesiredRotation();
	UFUNCTION()
		void DirectionalDodge();
	UPROPERTY(BlueprintReadWrite)
		AWeaponBase* WeaponPtr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		bool CanDodge;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool IsEquipped;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		bool IsDodging;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsRunning;
	UFUNCTION()
		bool HadMovementInput();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool CanMove;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Dodge")
		float DodgeDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool CanEnterIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsFalling;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float SprintSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float JogSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		UAnimMontage* DefaultDodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		UAnimMontage* DefaultJump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitAnims")
		UAnimMontage* DefaultHitReaction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitAnims")
		UAnimMontage* DefaultDeath;
	UPROPERTY()
		FTimerHandle UnusedDodgeHandle;
	UPROPERTY()
		FTimerHandle UnusedMovementHandle;
	UPROPERTY()
		float DefaultFriction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AWeaponBase> Weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int EquippedWeapon;
	UPROPERTY()
		bool IsSheathing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool IsAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		int CurrentAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool CanAttack;
	UFUNCTION()
		virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
		void OnDeath(UAnimMontage* animMontage, bool bInterrupted);
	UPROPERTY()
		float FAxis;
	UPROPERTY()
		float RAxis;
	UFUNCTION()
		virtual void Falling() override;
	UFUNCTION()
		virtual void Landed(const FHitResult& Hit) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

