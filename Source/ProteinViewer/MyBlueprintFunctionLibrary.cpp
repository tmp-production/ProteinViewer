// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#include "MyBlueprintFunctionLibrary.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "readcif.h"

using namespace readcif;

void UMyBlueprintFunctionLibrary::OpenFileDialog(
	const FString& DialogTitle, const FString& DefaultPath,
	const FString& FileTypes, TArray<FString>& OutFileNames)
{
	if (GEngine)
	{
		if (GEngine->GameViewport)
		{
			const void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
			IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
			if (DesktopPlatform)
			{
				DesktopPlatform->OpenFileDialog(
					ParentWindowHandle, DialogTitle, DefaultPath,
					FString(""), FileTypes, 0, OutFileNames);
			}
		}
	}
}

void UMyBlueprintFunctionLibrary::ParseInputFile(
	const FString& Filename, const float Scale,
	TArray<FTransform>& AtomTransforms)
{
	CIFFile FileParser;
	FileParser.register_heuristic_stylized_detection();
	FileParser.register_category("atom_site", [&FileParser, &AtomTransforms, Scale]()
	{
		CIFFile::ParseValues ParseValues;
		FVector AtomVector;

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_x", true),
			[&AtomVector, Scale](const char* Start)
			{
				AtomVector.X = Scale * str_to_float(Start);
			});

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_y", true),
			[&AtomVector, Scale](const char* Start)
			{
				AtomVector.Y = Scale * str_to_float(Start);
			});

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_z", true),
			[&AtomVector, Scale](const char* Start)
			{
				AtomVector.Z = Scale * str_to_float(Start);
			});

		while (FileParser.parse_row(ParseValues))
		{
			AtomTransforms.Add(FTransform(AtomVector));
		}
	});

	FileParser.parse_file(TCHAR_TO_ANSI(*Filename));
}
