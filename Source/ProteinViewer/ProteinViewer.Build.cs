// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using UnrealBuildTool;

public class ProteinViewer : ModuleRules
{
	public ProteinViewer(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new[] {"Core", "CoreUObject", "Engine", "InputCore"});
		PrivateDependencyModuleNames.AddRange(new[] {"Slate", "SlateCore", "Vina"});
		
		bEnableExceptions = true;  // could fix Error C4530
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;  // Error C7555 fix
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}