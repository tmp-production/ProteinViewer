#pragma once
#include "FResidue.h"
#include "FChain.generated.h"

USTRUCT(BlueprintType)
struct FChain
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Model")
	TArray<FResidue> residues;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Model")
	FString chainID;

	FChain()
	{
		this->residues = TArray<FResidue>();
		this->chainID = FString();
	}

	FChain(FString id)
	{
		this->residues = TArray<FResidue>();
		this->chainID = id;
	}

	FChain(TArray<FResidue> Residues,FString id)
	{
		this->residues = Residues;
		this->chainID = id;
	}
};
