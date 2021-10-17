// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DF_AttackTracer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DF_API UDF_AttackTracer : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	TArray<FHitResult>HitResult; //Since we will be tracing with multiple rays we will have to save results from all arrays

	TArray<AActor*>HitActors; //Since the sword can hit multiple people

	AController* EventInstigator;

	TSubclassOf<UDamageType>DamageTypeClass;

	FVector LastLocation1;

	FVector LastLocation2;

	FVector LastLocation3;

	class ADF_Character* Player;

	class USkeletalMeshComponent* Weapon;

	TArray<AActor*>ActorsToIgnore;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	
};
