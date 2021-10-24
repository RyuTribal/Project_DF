// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DF_BaseAttributes.generated.h"

// User macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 
/**
 * 
 */
UCLASS()
class PROJECT_DF_API UDF_BaseAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:
	UDF_BaseAttributes();


	//Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDF_BaseAttributes, Health);


	//Stamina

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDF_BaseAttributes, Stamina);


	//Attack Power

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UDF_BaseAttributes, AttackPower);




	
};
