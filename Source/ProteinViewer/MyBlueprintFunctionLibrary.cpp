// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#include "MyBlueprintFunctionLibrary.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "readcif.h"
#include "pdb/PDBParser.h"
#include "ribbon/Ribbon.h"

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
	const FString& Filename,
	TArray<FAtomStruct>& AtomStructs)
{
	CIFFile FileParser;
	FileParser.register_heuristic_stylized_detection();
	FileParser.register_category("atom_site", [&FileParser, &AtomStructs]()
	{
		CIFFile::ParseValues ParseValues;
		FAtomStruct Atom;

		ParseValues.emplace_back(
			FileParser.get_column("type_symbol", true),
			[&Atom](const char* Start)
			{
				if (Start[1] == ' ') // If Element type is 1 char. For example: C, O, N
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
			[&Atom](const char* Start)
			{
				Atom.coordinates.X = str_to_float(Start);
			});

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_y", true),
			[&Atom](const char* Start)
			{
				Atom.coordinates.Y = str_to_float(Start);
			});

		ParseValues.emplace_back(
			FileParser.get_column("Cartn_z", true),
			[&Atom](const char* Start)
			{
				Atom.coordinates.Z = str_to_float(Start);
			});

		while (FileParser.parse_row(ParseValues))
		{
			AtomStructs.Add(Atom);
		}
	});

	FileParser.parse_file(TCHAR_TO_ANSI(*Filename));
}

void UMyBlueprintFunctionLibrary::LoadPDBModel(
	TArray<FChain>& chains,
	TArray<FAtomStruct>& AtomStructs,
	const FString& File
)
{
	UE_LOG(LogTemp, Log, TEXT("Loading file: %s"), *File);

	const char* filename = TCHAR_TO_UTF8(*File);
	const auto model = pdb::PDBParser::read(filename);

	UE_LOG(LogTemp, Log, TEXT("Parsed a molecule with %d atoms"), model.atoms.size());
	for (pdb::Atom atom : model.atoms)
	{
		AtomStructs.Add(FAtomStruct(FString(atom.element.c_str()),
		FVector(atom.x, atom.y, atom.z)));
	}

	for (const auto& chain : model.chains)
	{
		UE_LOG(LogTemp, Log, TEXT("Chain construction"));

		FChain fchain = FChain(chain.chainID.c_str());
		fchain.residues = ribbon::createResidueMeshes(chain);

		UE_LOG(LogTemp, Log, TEXT("Chain constructed, %d residues"), fchain.residues.Num());

		chains.Add(fchain);
	}
}
