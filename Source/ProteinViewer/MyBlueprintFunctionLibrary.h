// Copyright (c) 2021 Novosibirsk State University. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROTEINVIEWER_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Something")
    static void DoSomething();

	UFUNCTION(BlueprintCallable, Category = "Something")
	static FTransform loadTransform();
};
