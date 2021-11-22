// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#include "MyBlueprintFunctionLibrary.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "readcif.h"
#include "Kismet/KismetStringLibrary.h"

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
		TArray<FVector>& Vertices,
		TArray<int32>& Indexes)
{
	FString file = FPaths::ProjectDir();
	file.Append(TEXT("triangles.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	TArray<FString> FileContent;
	// Always first check if the file that you want to manipulate exist.
	if (FileManager.FileExists(*file))
	{
		// We use the LoadFileToString to load the file into
		if(FFileHelper::LoadFileToStringArray(FileContent,*file))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Text From File %s Readed"), *file);
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Number of lines readed: %d"), FileContent.Num());
			int index = 0; 
			int flag = 1;
			for (FString line : FileContent)
			{
				if (flag == 1) {
					flag = 2;
					UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Line parse %s"), *line);
				}
				TArray<FString> verticeCoordinates = UKismetStringLibrary::ParseIntoArray(line, FString(" "));
				if (flag == 2) {
					flag = 3;
					UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Count %d"), verticeCoordinates.Num());
				}
				if (verticeCoordinates.Num() == 3)
				{
					if (flag == 3) {
						flag = 4;
						UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Creating Vector %s %s %s"),
							*verticeCoordinates[0], *verticeCoordinates[1], *verticeCoordinates[2]);
					}
					FVector vertex = FVector(
						FCString::Atof(*(verticeCoordinates[0])),
						FCString::Atof(*(verticeCoordinates[1])),
						FCString::Atof(*(verticeCoordinates[2])));
					Vertices.Add(vertex);
					Indexes.Add(index);
					index++;
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Vertices.Num: %d"), Vertices.Num());
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Indexes.Num: %d"), Indexes.Num());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"),*file);
	}
	
}