// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using UnrealBuildTool;

public class Vina : ModuleRules
{
	public Vina(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.Add("Boost");
		ShadowVariableWarningLevel = WarningLevel.Off;

		bUseRTTI = true;
		bEnableUndefinedIdentifierWarnings = false;
	}
}