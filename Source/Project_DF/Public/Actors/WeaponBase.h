// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class PROJECT_DF_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
		float BaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
		int id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
		int AmmountLightAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* UnSheathe;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* Sheathe;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* AttackCombo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* Dodge;

};
