// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using UnrealBuildTool;

public class ProteinViewer : ModuleRules
{
	public ProteinViewer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		bEnableExceptions = true;  // could fix Error C4530
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}