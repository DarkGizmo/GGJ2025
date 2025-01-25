// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GGJ2025/GGJ2025GameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGGJ2025GameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
GGJ2025_API UClass* Z_Construct_UClass_AGGJ2025GameMode();
GGJ2025_API UClass* Z_Construct_UClass_AGGJ2025GameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_GGJ2025();
// End Cross Module References

// Begin Class AGGJ2025GameMode
void AGGJ2025GameMode::StaticRegisterNativesAGGJ2025GameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGGJ2025GameMode);
UClass* Z_Construct_UClass_AGGJ2025GameMode_NoRegister()
{
	return AGGJ2025GameMode::StaticClass();
}
struct Z_Construct_UClass_AGGJ2025GameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "GGJ2025GameMode.h" },
		{ "ModuleRelativePath", "GGJ2025GameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGGJ2025GameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AGGJ2025GameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_GGJ2025,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGGJ2025GameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGGJ2025GameMode_Statics::ClassParams = {
	&AGGJ2025GameMode::StaticClass,
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
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGGJ2025GameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AGGJ2025GameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGGJ2025GameMode()
{
	if (!Z_Registration_Info_UClass_AGGJ2025GameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGGJ2025GameMode.OuterSingleton, Z_Construct_UClass_AGGJ2025GameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGGJ2025GameMode.OuterSingleton;
}
template<> GGJ2025_API UClass* StaticClass<AGGJ2025GameMode>()
{
	return AGGJ2025GameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGGJ2025GameMode);
AGGJ2025GameMode::~AGGJ2025GameMode() {}
// End Class AGGJ2025GameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_GGJ2025_GGJ2025_Source_GGJ2025_GGJ2025GameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGGJ2025GameMode, AGGJ2025GameMode::StaticClass, TEXT("AGGJ2025GameMode"), &Z_Registration_Info_UClass_AGGJ2025GameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGGJ2025GameMode), 1729035181U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GGJ2025_GGJ2025_Source_GGJ2025_GGJ2025GameMode_h_796756339(TEXT("/Script/GGJ2025"),
	Z_CompiledInDeferFile_FID_GGJ2025_GGJ2025_Source_GGJ2025_GGJ2025GameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GGJ2025_GGJ2025_Source_GGJ2025_GGJ2025GameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
