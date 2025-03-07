// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MProject : ModuleRules
{
	public MProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "CSCoreLibrary", "FirebaseFeatures" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG", "OnlineSubsystemUtils" });
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");
			PrivateDependencyModuleNames.Add("AndroidPermission");
		}
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string SourcePath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(SourcePath, "AndroidAPITemplate_APL.xml"));
		}
	}
}
