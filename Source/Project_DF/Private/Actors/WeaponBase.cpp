// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BaseDamage = 100.f;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	UnSheathe = CreateDefaultSubobject<UAnimMontage>(TEXT("UnSheathe"));
	Sheathe = CreateDefaultSubobject<UAnimMontage>(TEXT("Sheathe"));
	AttackCombo = CreateDefaultSubobject<UAnimMontage>(TEXT("AttackCombo"));
	Dodge = CreateDefaultSubobject<UAnimMontage>(TEXT("Dodge"));
	RootComponent = WeaponMesh;
	AmmountLightAttacks = 3;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

