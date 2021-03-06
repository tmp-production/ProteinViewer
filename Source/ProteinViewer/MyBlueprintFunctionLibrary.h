// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Structs/AtomStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structs/FChain.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UCLASS()
class PROTEINVIEWER_API UMyBlueprintFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** 
	 * Opens the "open file" dialog for the platform
	 *
	 * @param DialogTitle The text for the title of the dialog window
	 * @param DefaultPath The path where the file dialog will open initially
	 * @param FileTypes The type filters to show in the dialog. This string should be a "|" delimited list of (Description|Extensionlist) pairs. Extensionlists are ";" delimited.
	 * @param OutFileNames The filenames that were selected in the dialog
	 */
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	static void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath,
	                           const FString& FileTypes, TArray<FString>& OutFileNames);

	/**
	 * Reads the specified PDBx/mmCIF file and tries to parse it
	 *
	 * @param Filename The filename of the file to open
	 * @param AtomStructs The FAtomStruct array representing the structures of the atoms
	 */
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	static void ParseInputFile(
		const FString& Filename,
		TArray<FAtomStruct>& AtomStructs);

	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	static void LoadPDBModel(
		TArray<FChain>& chains,
		TArray<FAtomStruct>& AtomStructs,
		const FString& File);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FDockingDelegate, float, Progress);

	UFUNCTION(BlueprintCallable, Category = "Docking")
	static FString PerformDocking(const FString& ReceptorFilePath, const FString& LigandFilePath,
	                              float CenterX, float CenterY, float CenterZ,
	                              float SizeX, float SizeY, float SizeZ,
	                              FDockingDelegate DockingDelegate,
	                              int Exhaustiveness = 8, int NumPoses = 20);

	UFUNCTION(BlueprintCallable, Category = "Docking")
	static void PerformTestDocking(FDockingDelegate DockingDelegate);
};
