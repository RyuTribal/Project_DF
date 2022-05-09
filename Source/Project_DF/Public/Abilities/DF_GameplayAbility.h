// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Project_DF/Project_DF.h"
#include "DF_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DF_API UDF_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UDF_GameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		EGASAbilityInputID AbilityInputID = EGASAbilityInputID::None;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		bool IsPassive;
};
