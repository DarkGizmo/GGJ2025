// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GGJ2025 : ModuleRules
{
	public GGJ2025(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
