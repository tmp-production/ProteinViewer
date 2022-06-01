// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using UnrealBuildTool;
using System.Runtime.InteropServices;

public class ProteinViewerTarget : TargetRules
{
	public ProteinViewerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(new string[] {"ProteinViewer"});

		if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
		{
			bOverrideBuildEnvironment = true;
			AdditionalCompilerArguments = "-Wno-unused-but-set-variable -Wno-unknown-pragmas";
		}
	}
}