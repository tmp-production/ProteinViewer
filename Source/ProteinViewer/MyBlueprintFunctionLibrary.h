// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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
	 * Reads the specified file and tries to parse it into an FTransform object.
	 *
	 * @param Filename The filename of the file to open
	 * @return The resulting FTransform object
	 */
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	static FTransform ParseInputFile(const FString Filename);
};
