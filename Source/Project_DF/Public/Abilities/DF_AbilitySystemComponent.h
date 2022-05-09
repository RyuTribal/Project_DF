// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Project_DF/Project_DF.h"
#include "AbilitySystemComponent.h"
#include "DF_AbilitySystemComponent.generated.h"

class UDF_GameplayAbility;

/**
 * Subclass of ability system component with game-specific data
 * Most games will need to make a game-specific subclass to provide utility functions
 */
UCLASS()
class PROJECT_DF_API UDF_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Constructors and overrides
	UDF_AbilitySystemComponent();

	/** Returns a list of currently active ability instances that match the tags */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UDF_GameplayAbility*>& ActiveAbilities);


	/** Version of function in AbilitySystemGlobals that returns correct type */
	static UDF_AbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

};
