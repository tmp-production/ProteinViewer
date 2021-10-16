// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#include "MyBlueprintFunctionLibrary.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"

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

FTransform UMyBlueprintFunctionLibrary::ParseInputFile(const FString Filename)
{
	TArray<FString> InputStrings;
	FFileHelper::LoadFileToStringArray(InputStrings, GetData(Filename));

	const float x = FCString::Atof(*InputStrings[0]);
	const float y = FCString::Atof(*InputStrings[1]);
	const float z = FCString::Atof(*InputStrings[2]);

	return FTransform(FVector(x, y, z));
}
