// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExoPhysicsCpp : ModuleRules
{
	public ExoPhysicsCpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosSolverEngine", "GeometryCollectionEngine", "Chaos" });
	}
}
