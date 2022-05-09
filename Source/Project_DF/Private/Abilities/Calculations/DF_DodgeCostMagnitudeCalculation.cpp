// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Calculations/DF_DodgeCostMagnitudeCalculation.h"
#include "Abilities/DF_AttributeSet.h"

FGameplayEffectAttributeCaptureDefinition Stamina;

UDF_DodgeCostMagnitudeCalculation::UDF_DodgeCostMagnitudeCalculation()
{
	Stamina.AttributeToCapture = UDF_AttributeSet::GetStaminaAttribute();
	Stamina.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Stamina.bSnapshot = false;

	RelevantAttributesToCapture.Add(Stamina);
}

float UDF_DodgeCostMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayEffectAttributeCaptureSpec* StaminaDef = Spec.CapturedRelevantAttributes.FindCaptureSpecByDefinition(Stamina, false);
	//Get the owning GameplayEffect Spec so that you can use its variables and tags.
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//Aggregator Evaluate Parameters used during the attribute capture.
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	float CharacterStamina = 0.f;
	float StaminaCost = 40.f;
	StaminaDef->AttemptCalculateAttributeMagnitude(EvaluationParameters, CharacterStamina);
	if(!(CharacterStamina <= 0.f) && CharacterStamina < StaminaCost)
	{
		StaminaCost = CharacterStamina;
	}
	return StaminaCost;
}
