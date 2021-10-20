// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Actors/DF_Character.h"
#include "RotateOnInput.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DF_API URotateOnInput : public UAnimNotifyState
{
	GENERATED_BODY()

	class ADF_Character* Owner;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
};
