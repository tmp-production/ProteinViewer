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
	TArray<FAtomStruct>& AtomStructs)
{
	CIFFile FileParser;
	FileParser.register_heuristic_stylized_detection();
	FileParser.register_category("atom_site", [&FileParser, &AtomStructs, Scale]()
	{
		CIFFile::ParseValues ParseValues;
		FAtomStruct Atom;

		ParseValues.emplace_back(
			FileParser.get_column("type_symbol", true),
			[&Atom](const char* Start)
			{
				if(Start[1] == ' ') // If Element type is 1 char. For example: C, O, N
				{
					Atom.Element = FString(1, Start);
				}
				else // If Element type is 2 chars. For example: FE
				{
					Atom.Element = FString(2, Start);
				}
			});
		
		ParseValues.emplace_back(
			FileParser.get_column("Cartn_x", true),
			[&Atom, Scale](const char* Start)
			{
				Atom.coordinates.X = Scale * str_to_float(Start);
			});

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_y", true),
			[&Atom, Scale](const char* Start)
			{
				Atom.coordinates.Y = Scale * str_to_float(Start);
			});

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_z", true),
			[&Atom, Scale](const char* Start)
			{
				Atom.coordinates.Z = Scale * str_to_float(Start);
			});

		while (FileParser.parse_row(ParseValues))
		{
			AtomStructs.Add(Atom);
		}
	});

	FileParser.parse_file(TCHAR_TO_ANSI(*Filename));
}