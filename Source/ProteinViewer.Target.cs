// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProteinViewerTarget : TargetRules
{
	public ProteinViewerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ProteinViewer" } );
	}
}
