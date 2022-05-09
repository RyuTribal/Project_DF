// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DF_AttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void UDF_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//So values don't go under or over min and max
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}

	if (Data.EvaluatedData.Attribute == GetSinmeterAttribute())
	{
		SetSinmeter(FMath::Clamp(GetSinmeter(), 0.f, GetMaxSinmeter()));
	}
}
