// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using UnrealBuildTool;
using System.Runtime.InteropServices;

public class ProteinViewerEditorTarget : TargetRules
{
	public ProteinViewerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ProteinViewer" } );
		
		if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
		{
			bOverrideBuildEnvironment = true;
			AdditionalCompilerArguments = "-Wno-unused-but-set-variable -Wno-unknown-pragmas";
		}
	}
}
