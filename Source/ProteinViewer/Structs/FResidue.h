#pragma once
#include "MeshSectionStruct.h"
#include "FResidue.generated.h"

UENUM(BlueprintType, Category = "Model")
enum EResidueType
{
	ResidueTypeCoil     UMETA(DisplayName = "Coil"),
	ResidueTypeHelix    UMETA(DisplayName = "Helix"),
	ResidueTypeStrand   UMETA(DisplayName = "Strand"),
};

USTRUCT(BlueprintType)
struct FResidue
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Render")
	FMeshSectionStruct MeshSection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Model")
	TEnumAsByte<EResidueType> type;

	FResidue()
	{
		MeshSection = *(new FMeshSectionStruct());
		type = EResidueType::ResidueTypeCoil;
	}
	
	FResidue(FMeshSectionStruct section, TEnumAsByte<EResidueType> type)
	{
		MeshSection = section;
		this->type = type;
	}
};
