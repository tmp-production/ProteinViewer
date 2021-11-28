#pragma once
#include "MeshSectionStruct.generated.h"
USTRUCT(BlueprintType)
struct FMeshSectionStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Student")
	TArray<FVector> Vertices;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Student")
	TArray<int32> Indexes;

	FMeshSectionStruct()
	{
		Vertices = TArray<FVector>();
		Indexes = TArray<int32>();
	}

	FMeshSectionStruct(TArray<FVector> vertices, TArray<int32> indexes)
	{
		Vertices = vertices;
		Indexes = indexes;
	}
};
