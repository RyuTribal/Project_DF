// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DF_GameplayAbility_DodgeBase.h"

#include "Abilities/DF_PlayMontageAndWait.h"
#include "Kismet/KismetMathLibrary.h"

UDF_GameplayAbility_DodgeBase::UDF_GameplayAbility_DodgeBase()
{
	DefaultDodgeAnim = CreateDefaultSubobject<UAnimMontage>(TEXT("Default Dodge Animation"));
}

void UDF_GameplayAbility_DodgeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ADF_Character* AbilityOwner = Cast<ADF_Character>(ActorInfo->OwnerActor);
	AbilityOwner->CanAttack = false;
	AbilityOwner->IsDodging = true;
	AbilityOwner->CanMove = false;
	UCharacterMovementComponent* cMove = AbilityOwner->GetCharacterMovement();
	AbilityOwner->DefaultFriction = cMove->BrakingFrictionFactor;
	cMove->BrakingFrictionFactor = 0.f; //Removes friction since it messes with how far the character can be launched
	FVector DodgeVector = DirectionalDodge(AbilityOwner);
	AbilityOwner->LaunchCharacter(FVector(DodgeVector.X, DodgeVector.Y, 0.f).GetSafeNormal() * AbilityOwner->DodgeDistance, true, true);
	UAnimMontage* MontageToPlay;
	if(AbilityOwner->IsEquipped)
	{
		MontageToPlay = AbilityOwner->WeaponPtr->MultiDirDodge;
	}
	else
	{
		MontageToPlay = DefaultDodgeAnim;
	}
	UDF_PlayMontageAndWait* PlayMontageAndWait = UDF_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, FName("Dodge"), MontageToPlay, FGameplayTagContainer::EmptyContainer, 1.0f, AbilityOwner->IsLocked ? GetStartSection(AbilityOwner) : NAME_None, true, 0.0f);
	PlayMontageAndWait->OnBlendOut.AddDynamic(this, &UDF_GameplayAbility_DodgeBase::OnBlendOut);
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &UDF_GameplayAbility_DodgeBase::OnBlendOut);
	PlayMontageAndWait->Activate();
	
	
}

FVector UDF_GameplayAbility_DodgeBase::DirectionalDodge(ADF_Character* AbilityOwner)
{
	FVector DodgeVector;
	if (AbilityOwner->GetLastMovementInputVector().Size() != 0)
	{
		DodgeVector = AbilityOwner->GetLastMovementInputVector();
	}
	else
	{
		DodgeVector = AbilityOwner->GetActorForwardVector();
	}
	if(!AbilityOwner->IsLocked)
	{
		AbilityOwner->SetActorRotation(AbilityOwner->GetDesiredRotation()); // Gets back an input rotation
	}
	return DodgeVector;

}

FName UDF_GameplayAbility_DodgeBase::GetStartSection(ADF_Character* AbilityOwner)
{
	FName Section;
	bool FAxisBigger = UKismetMathLibrary::Abs(AbilityOwner->FAxis) >= UKismetMathLibrary::Abs(AbilityOwner->RAxis);
	if (FAxisBigger)
	{
		if (AbilityOwner->FAxis >= 0)
		{
			Section = FName("Dodge_F");
		}
		else
		{
			Section = FName("Dodge_B");
		}
	}
	else
	{
		if (AbilityOwner->RAxis >= 0)
		{
			Section = FName("Dodge_R");
		}
		else
		{
			Section = FName("Dodge_L");
		}
	}
	return Section;
}

void UDF_GameplayAbility_DodgeBase::OnBlendOut(FGameplayTag EventTag,
	FGameplayEventData EventData)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UDF_GameplayAbility_DodgeBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ADF_Character* AbilityOwner = Cast<ADF_Character>(ActorInfo->OwnerActor);
	AbilityOwner->GetCharacterMovement()->StopMovementImmediately(); // This is more of a safety meassure so that no movement is performed before the dodge is complete
	AbilityOwner->GetCharacterMovement()->BrakingFrictionFactor = AbilityOwner->DefaultFriction; // Gives friction back to the character
	AbilityOwner->IsDodging = false;
	AbilityOwner->CanMove = true;
}

