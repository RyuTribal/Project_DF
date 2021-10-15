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
		void StartIdleAnim();		// Changes the idle animation variables
	UFUNCTION()
		void ResetIdleAnim();		// Resets the idle animation variables


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Dodge")
		float DodgeDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		bool IsDodging;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		bool CanDodge;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool CanMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool CanEnterIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		int RandomIdleValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float IdleOffset;
	UPROPERTY()
		FTimerHandle UnusedDodgeHandle;
	UPROPERTY()
		FTimerHandle UnusedMovementHandle;
	UPROPERTY()
		float DefaultFriction;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

