// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStates/DF_AttackTracer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "Actors/DF_Character.h"
#include "Actors/WeaponBase.h"

void UDF_AttackTracer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Player = Cast<ADF_Character>(MeshComp->GetOwner());
	if (Player)
	{
		Weapon = Player->WeaponPtr->WeaponMesh;
		ActorsToIgnore = { MeshComp->GetOwner(), Player->WeaponPtr };
		LastLocation1 = Weapon->GetSocketLocation("Trace1");
		LastLocation2 = Weapon->GetSocketLocation("Trace2");
		LastLocation3 = Weapon->GetSocketLocation("Trace3");
	}
}
void UDF_AttackTracer::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (Player) {
		for (int j = 0; j < 3; j++) {
			// Change none on EDebugTrace for drawing out the trace line
			UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), LastLocation1, Weapon->GetSocketLocation("Trace" + j), FVector(5, 30, 50), Weapon->GetComponentRotation(), ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
			for (int i = 0; i < HitResult.Num(); i++)
			{
				AActor* HitActor = HitResult[i].GetActor();
				if (!HitActors.Contains(HitActor)) {
					HitActors.Add(HitActor);
					UGameplayStatics::ApplyDamage(HitActor, 10.f, EventInstigator, Player, DamageTypeClass);
				}
			}
			LastLocation1 = Weapon->GetSocketLocation("Trace" + j);
		}
	}
}

void UDF_AttackTracer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
