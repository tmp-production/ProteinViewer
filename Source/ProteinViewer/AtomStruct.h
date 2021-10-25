#pragma once
#include "AtomStruct.generated.h" // 1 hour of debugging/googling help to find this...
USTRUCT(BlueprintType)
struct FAtomStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Student")
	FString Element;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Student")
	FVector coordinates;

	FAtomStruct()
	{
		Element = FString();
		coordinates = FVector();
	}
};
