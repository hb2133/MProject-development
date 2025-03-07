// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CSCoreLibrary : ModuleRules
{
	public CSCoreLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput" });
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = true;
		PublicDependencyModuleNames.Add("ApplicationCore");
		PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("CoreUObject");
		PublicDependencyModuleNames.Add("Engine");
		PublicDependencyModuleNames.Add("InputCore");

		PublicDependencyModuleNames.Add("UMG");
		PublicDependencyModuleNames.Add("Slate");
		PublicDependencyModuleNames.Add("SlateCore");
		PublicDependencyModuleNames.Add("Paper2D");

		PublicDependencyModuleNames.Add("Json");
		PublicDependencyModuleNames.Add("JsonUtilities");
		
		PrivateDependencyModuleNames.Add("ApplicationCore");

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
