// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECT_DF_DF_Character_generated_h
#error "DF_Character.generated.h already included, missing '#pragma once' in DF_Character.h"
#endif
#define PROJECT_DF_DF_Character_generated_h

#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_SPARSE_DATA
#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStopDodge); \
	DECLARE_FUNCTION(execDodge); \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStopDodge); \
	DECLARE_FUNCTION(execDodge); \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADF_Character(); \
	friend struct Z_Construct_UClass_ADF_Character_Statics; \
public: \
	DECLARE_CLASS(ADF_Character, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_DF"), NO_API) \
	DECLARE_SERIALIZER(ADF_Character)


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_INCLASS \
private: \
	static void StaticRegisterNativesADF_Character(); \
	friend struct Z_Construct_UClass_ADF_Character_Statics; \
public: \
	DECLARE_CLASS(ADF_Character, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Project_DF"), NO_API) \
	DECLARE_SERIALIZER(ADF_Character)


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADF_Character(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADF_Character) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADF_Character); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADF_Character); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADF_Character(ADF_Character&&); \
	NO_API ADF_Character(const ADF_Character&); \
public:


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADF_Character(ADF_Character&&); \
	NO_API ADF_Character(const ADF_Character&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADF_Character); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADF_Character); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADF_Character)


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__DodgeDistance() { return STRUCT_OFFSET(ADF_Character, DodgeDistance); } \
	FORCEINLINE static uint32 __PPO__IsDodging() { return STRUCT_OFFSET(ADF_Character, IsDodging); } \
	FORCEINLINE static uint32 __PPO__DodgeDelay() { return STRUCT_OFFSET(ADF_Character, DodgeDelay); } \
	FORCEINLINE static uint32 __PPO__CanMove() { return STRUCT_OFFSET(ADF_Character, CanMove); } \
	FORCEINLINE static uint32 __PPO__UnusedHandle() { return STRUCT_OFFSET(ADF_Character, UnusedHandle); } \
	FORCEINLINE static uint32 __PPO__DefaultFriction() { return STRUCT_OFFSET(ADF_Character, DefaultFriction); }


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_21_PROLOG
#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_PRIVATE_PROPERTY_OFFSET \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_SPARSE_DATA \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_RPC_WRAPPERS \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_INCLASS \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_PRIVATE_PROPERTY_OFFSET \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_SPARSE_DATA \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_INCLASS_NO_PURE_DECLS \
	Project_DF_Source_Project_DF_Public_Actors_DF_Character_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECT_DF_API UClass* StaticClass<class ADF_Character>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_DF_Source_Project_DF_Public_Actors_DF_Character_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
