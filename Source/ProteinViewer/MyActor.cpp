// Copyright (c) 2021 Novosibirsk State University. All rights reserved.


#include "MyActor.h"

#include <fstream>

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMeshComponent;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	FVector teleportDot = loadInputData();
	TeleportTo(FVector(420,420,420),FRotator());
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MyMeshComponent->AddLocalRotation(FRotator(0.f,1.f,0.f));
}




FVector AMyActor::loadInputData()
{
	
	
	TArray<FString> inputStrings;
	FFileHelper::LoadFileToStringArray(inputStrings, *(FPaths::ProjectDir() + "input.txt"));
	FString* array = inputStrings.GetData();
	float x, y, z;
	x = FCString::Atof(*array[0]);
	y = FCString::Atof(*array[1]);
	z = FCString::Atof(*array[2]);

	std::ofstream myfile;
	myfile.open ("D:\\Repositories\\ProteinViewer\\example.txt");
	myfile << x << ' ' << y << ' ' << z;
	myfile.close();
	return FVector(x,y,z);
}

