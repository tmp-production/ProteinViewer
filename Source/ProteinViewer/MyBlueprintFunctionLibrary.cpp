// Copyright (c) 2021 Novosibirsk State University. All rights reserved.


#include "MyBlueprintFunctionLibrary.h"

#include "IMovieSceneTracksModule.h"

void UMyBlueprintFunctionLibrary::DoSomething()
{
	FFileHelper::SaveStringToFile(FString("Writing this to a file.\n"),*(FPaths::ProjectDir()+"example.txt"));
}


FTransform UMyBlueprintFunctionLibrary::loadTransform()
{
	TArray<FString> inputStrings;
	FFileHelper::LoadFileToStringArray(inputStrings, *(FPaths::ProjectDir() + "input.txt"));
	FString* array = inputStrings.GetData();
	float x, y, z;
	x = FCString::Atof(*array[0]);
	y = FCString::Atof(*array[1]);
	z = FCString::Atof(*array[2]);
	return FTransform(FVector(x,y,z));
}