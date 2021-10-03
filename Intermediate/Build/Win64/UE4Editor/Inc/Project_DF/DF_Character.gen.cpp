// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_DF/Public/Actors/DF_Character.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDF_Character() {}
// Cross Module References
	PROJECT_DF_API UClass* Z_Construct_UClass_ADF_Character_NoRegister();
	PROJECT_DF_API UClass* Z_Construct_UClass_ADF_Character();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Project_DF();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTimerHandle();
// End Cross Module References
	DEFINE_FUNCTION(ADF_Character::execStopDodge)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StopDodge();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADF_Character::execDodge)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Dodge();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADF_Character::execMoveRight)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Axis);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MoveRight(Z_Param_Axis);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADF_Character::execMoveForward)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Axis);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MoveForward(Z_Param_Axis);
		P_NATIVE_END;
	}
	void ADF_Character::StaticRegisterNativesADF_Character()
	{
		UClass* Class = ADF_Character::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Dodge", &ADF_Character::execDodge },
			{ "MoveForward", &ADF_Character::execMoveForward },
			{ "MoveRight", &ADF_Character::execMoveRight },
			{ "StopDodge", &ADF_Character::execStopDodge },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADF_Character_Dodge_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADF_Character_Dodge_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADF_Character_Dodge_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADF_Character, nullptr, "Dodge", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADF_Character_Dodge_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADF_Character_Dodge_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADF_Character_Dodge()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADF_Character_Dodge_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADF_Character_MoveForward_Statics
	{
		struct DF_Character_eventMoveForward_Parms
		{
			float Axis;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Axis;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ADF_Character_MoveForward_Statics::NewProp_Axis = { "Axis", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DF_Character_eventMoveForward_Parms, Axis), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ADF_Character_MoveForward_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ADF_Character_MoveForward_Statics::NewProp_Axis,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADF_Character_MoveForward_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADF_Character_MoveForward_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADF_Character, nullptr, "MoveForward", nullptr, nullptr, sizeof(DF_Character_eventMoveForward_Parms), Z_Construct_UFunction_ADF_Character_MoveForward_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ADF_Character_MoveForward_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADF_Character_MoveForward_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADF_Character_MoveForward_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADF_Character_MoveForward()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADF_Character_MoveForward_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADF_Character_MoveRight_Statics
	{
		struct DF_Character_eventMoveRight_Parms
		{
			float Axis;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Axis;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ADF_Character_MoveRight_Statics::NewProp_Axis = { "Axis", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DF_Character_eventMoveRight_Parms, Axis), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ADF_Character_MoveRight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ADF_Character_MoveRight_Statics::NewProp_Axis,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADF_Character_MoveRight_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADF_Character_MoveRight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADF_Character, nullptr, "MoveRight", nullptr, nullptr, sizeof(DF_Character_eventMoveRight_Parms), Z_Construct_UFunction_ADF_Character_MoveRight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ADF_Character_MoveRight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADF_Character_MoveRight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADF_Character_MoveRight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADF_Character_MoveRight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADF_Character_MoveRight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADF_Character_StopDodge_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADF_Character_StopDodge_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADF_Character_StopDodge_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADF_Character, nullptr, "StopDodge", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADF_Character_StopDodge_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADF_Character_StopDodge_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADF_Character_StopDodge()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADF_Character_StopDodge_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADF_Character_NoRegister()
	{
		return ADF_Character::StaticClass();
	}
	struct Z_Construct_UClass_ADF_Character_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DodgeDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DodgeDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsDodging_MetaData[];
#endif
		static void NewProp_IsDodging_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsDodging;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DodgeDelay_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DodgeDelay;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanMove_MetaData[];
#endif
		static void NewProp_CanMove_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanMove;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UnusedHandle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UnusedHandle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultFriction_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DefaultFriction;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADF_Character_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_DF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADF_Character_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADF_Character_Dodge, "Dodge" }, // 2213699326
		{ &Z_Construct_UFunction_ADF_Character_MoveForward, "MoveForward" }, // 1729978432
		{ &Z_Construct_UFunction_ADF_Character_MoveRight, "MoveRight" }, // 1098666946
		{ &Z_Construct_UFunction_ADF_Character_StopDodge, "StopDodge" }, // 3629355543
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Actors/DF_Character.h" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "// The spring arm so that the camera doesn't clip through the wall\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
		{ "ToolTip", "The spring arm so that the camera doesn't clip through the wall" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADF_Character, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_CameraBoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_CameraBoom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "// The actual camera\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
		{ "ToolTip", "The actual camera" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADF_Character, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_FollowCamera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_FollowCamera_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDistance_MetaData[] = {
		{ "Category", "Dodge" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDistance = { "DodgeDistance", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADF_Character, DodgeDistance), METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging_MetaData[] = {
		{ "Category", "Dodge" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	void Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging_SetBit(void* Obj)
	{
		((ADF_Character*)Obj)->IsDodging = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging = { "IsDodging", nullptr, (EPropertyFlags)0x0020080000020005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ADF_Character), &Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging_SetBit, METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDelay_MetaData[] = {
		{ "Category", "Dodge" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDelay = { "DodgeDelay", nullptr, (EPropertyFlags)0x0020080000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADF_Character, DodgeDelay), METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDelay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	void Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove_SetBit(void* Obj)
	{
		((ADF_Character*)Obj)->CanMove = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove = { "CanMove", nullptr, (EPropertyFlags)0x0020080000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ADF_Character), &Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove_SetBit, METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_UnusedHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_UnusedHandle = { "UnusedHandle", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADF_Character, UnusedHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_UnusedHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_UnusedHandle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_Character_Statics::NewProp_DefaultFriction_MetaData[] = {
		{ "ModuleRelativePath", "Public/Actors/DF_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADF_Character_Statics::NewProp_DefaultFriction = { "DefaultFriction", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADF_Character, DefaultFriction), METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::NewProp_DefaultFriction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::NewProp_DefaultFriction_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADF_Character_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_CameraBoom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_FollowCamera,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_IsDodging,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_DodgeDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_CanMove,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_UnusedHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADF_Character_Statics::NewProp_DefaultFriction,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADF_Character_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADF_Character>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADF_Character_Statics::ClassParams = {
		&ADF_Character::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADF_Character_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADF_Character_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_Character_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADF_Character()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADF_Character_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADF_Character, 2723597047);
	template<> PROJECT_DF_API UClass* StaticClass<ADF_Character>()
	{
		return ADF_Character::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADF_Character(Z_Construct_UClass_ADF_Character, &ADF_Character::StaticClass, TEXT("/Script/Project_DF"), TEXT("ADF_Character"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADF_Character);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
