// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStates/RotateOnInput.h"
#include "Actors/DF_Character.h"



void URotateOnInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Owner = Cast<ADF_Character>(MeshComp->GetOwner());
	
}
void URotateOnInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if(Owner)
	{
		FRotator NewRotation = FMath::RInterpTo(Owner->GetActorRotation(), Owner->GetDesiredRotation(), Owner->GetWorld()->DeltaTimeSeconds, 3.f);
		Owner->SetActorRotation(NewRotation);
	}
		
	
}