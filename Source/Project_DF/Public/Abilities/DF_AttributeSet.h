// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DF_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECT_DF_API UDF_AttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    //Health
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStats")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UDF_AttributeSet, Health);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStats")
        FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UDF_AttributeSet, MaxHealth);

    //Stamina
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStats")
        FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UDF_AttributeSet, Stamina);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStats")
        FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(UDF_AttributeSet, MaxStamina);

    //Sin meter
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStats")
        FGameplayAttributeData Sinmeter;
    ATTRIBUTE_ACCESSORS(UDF_AttributeSet, Sinmeter);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStats")
        FGameplayAttributeData MaxSinmeter;
    ATTRIBUTE_ACCESSORS(UDF_AttributeSet, MaxSinmeter);


};
