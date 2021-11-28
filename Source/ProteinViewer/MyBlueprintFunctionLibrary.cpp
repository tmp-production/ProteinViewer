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

void UMyBlueprintFunctionLibrary::ParseTriangles(
	TArray<FMeshSectionStruct>& sections
)
{
	FString File = FPaths::ProjectDir();
	File.Append(TEXT("4hhb.pdb"));

	const char* filename = TCHAR_TO_UTF8(*File);
	const auto model = pdb::PDBParser::read(filename);

	UE_LOG(LogTemp, Log, TEXT("Parsed a molecule with %d atoms"), model.atoms.size());

	for (const auto& chain : model.chains)
	{
		UE_LOG(LogTemp, Log, TEXT("Chain"));
		TArray<FVector> Vertices;
		TArray<int32> Indexes;
		for (const auto& triangle : ribbon::createChainMesh(chain))
		{
			for (const auto& vertex : triangle.vertices)
			{
				Vertices.Add(vertex.position);
				Indexes.Add(Indexes.Num());
			}
		}
		UE_LOG(LogTemp, Log, TEXT("Chain vertex count: %d"), Vertices.Num());
		sections.Add(FMeshSectionStruct(Vertices, Indexes));
	}

	// UE_LOG(LogTemp, Log, TEXT("Generated %d triangles for the mesh"), Indexes.Num() / 3);
}
