// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Obscura : ModuleRules
{
	public Obscura(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Json", "JsonUtilities"});
	}
}
