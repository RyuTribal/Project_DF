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
	if (Player && Player->WeaponPtr->WeaponMesh)
	{
		Player->CanDodge = false;
		Player->CanTrack = false;
		Weapon = Player->WeaponPtr->WeaponMesh;
		ActorsToIgnore = { MeshComp->GetOwner(), Player->WeaponPtr }; //All the actors that the sword will ignore
		/*
		 * These are the traces that exist inside the weapon. (check their skeletal meshes)
		 */
		LastLocation1 = Weapon->GetSocketLocation("Trace1");
		LastLocation2 = Weapon->GetSocketLocation("Trace2");
		LastLocation3 = Weapon->GetSocketLocation("Trace3");
	}
}
void UDF_AttackTracer::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (Player && Player->WeaponPtr->WeaponMesh) {
		for (int j = 0; j < 3; j++) { //Loops through the sockets
			/*
			 * Makes a box between the traces of the sockets.
			 * This makes so that even actors inbetween the traces get hit.
			 */
			UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), LastLocation1, Weapon->GetSocketLocation("Trace" + j), FVector(5, 30, 50), Weapon->GetComponentRotation(), ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
			for (int i = 0; i < HitResult.Num(); i++)
			{
				// Applies damage to all hit actors
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
	if(Player && Player->WeaponPtr->WeaponMesh)
	{
		Player->CanDodge = true;
		Player->CanTrack = true;
	}
	
}
