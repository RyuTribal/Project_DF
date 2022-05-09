// Copyright Epic Games, Inc. All Rights Reserved.

#include "Abilities/DF_AbilitySystemComponent.h"
#include "Actors/DF_Character.h"
#include "Abilities/DF_GameplayAbility.h"
#include "AbilitySystemGlobals.h"

UDF_AbilitySystemComponent::UDF_AbilitySystemComponent() {}

void UDF_AbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UDF_GameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<UDF_GameplayAbility>(ActiveAbility));
		}
	}
}

UDF_AbilitySystemComponent* UDF_AbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<UDF_AbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
