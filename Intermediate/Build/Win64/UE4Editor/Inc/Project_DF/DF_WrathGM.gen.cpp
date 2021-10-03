// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_DF/Public/GameModes/DF_WrathGM.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDF_WrathGM() {}
// Cross Module References
	PROJECT_DF_API UClass* Z_Construct_UClass_ADF_WrathGM_NoRegister();
	PROJECT_DF_API UClass* Z_Construct_UClass_ADF_WrathGM();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_Project_DF();
// End Cross Module References
	void ADF_WrathGM::StaticRegisterNativesADF_WrathGM()
	{
	}
	UClass* Z_Construct_UClass_ADF_WrathGM_NoRegister()
	{
		return ADF_WrathGM::StaticClass();
	}
	struct Z_Construct_UClass_ADF_WrathGM_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADF_WrathGM_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_DF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADF_WrathGM_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/DF_WrathGM.h" },
		{ "ModuleRelativePath", "Public/GameModes/DF_WrathGM.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADF_WrathGM_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADF_WrathGM>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADF_WrathGM_Statics::ClassParams = {
		&ADF_WrathGM::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ADF_WrathGM_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADF_WrathGM_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADF_WrathGM()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADF_WrathGM_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADF_WrathGM, 1119217885);
	template<> PROJECT_DF_API UClass* StaticClass<ADF_WrathGM>()
	{
		return ADF_WrathGM::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADF_WrathGM(Z_Construct_UClass_ADF_WrathGM, &ADF_WrathGM::StaticClass, TEXT("/Script/Project_DF"), TEXT("ADF_WrathGM"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADF_WrathGM);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
