// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DF_PlayMontageAndWait.h"
#include "Abilities/DF_GameplayAbility.h"
#include "Actors/DF_Character.h"
#include "DF_GameplayAbility_DodgeBase.generated.h"

UCLASS()
class PROJECT_DF_API UDF_GameplayAbility_DodgeBase : public UDF_GameplayAbility
{
	GENERATED_BODY()

public:
	UDF_GameplayAbility_DodgeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		UAnimMontage* DefaultDodgeAnim;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
		FVector DirectionalDodge(ADF_Character* AbilityOwner);
	UFUNCTION()
		FName GetStartSection(ADF_Character* AbilityOwner);

	UFUNCTION()
		void OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData);
};
