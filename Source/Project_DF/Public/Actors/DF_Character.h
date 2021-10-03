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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Dodge")
		float DodgeDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		bool IsDodging;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dodge")
		float DodgeDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool CanMove;
	UPROPERTY()
		FTimerHandle UnusedHandle;
	UPROPERTY()
		float DefaultFriction;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

