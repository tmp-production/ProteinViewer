// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

using System.IO;
using UnrealBuildTool;

public class Boost : ModuleRules
{
	public Boost(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseRTTI = true;
		//Type = ModuleType.External;
        string boostIncludePath = ProjectRoot + "..\\Boost\\boost_1_78_0";
		PublicSystemIncludePaths.Add(boostIncludePath);
		string boostLibPath = ProjectRoot + "..\\Boost\\boost_1_78_0\\stage\\lib";
		PublicSystemLibraryPaths.Add(boostLibPath);
	}
	
	public string ProjectRoot
    {
        get
        {
               return System.IO.Path.GetFullPath(
                   System.IO.Path.Combine(ModuleDirectory, "../../")
               );
        }
    }
}