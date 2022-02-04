// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFrameWork/Actor.h"
#include "Math/TransformNonVectorized.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("This is an error!"));
	//UE_LOG(LogTemp, Warning, TEXT("This is a warning"));
	//UE_LOG(LogTemp, Display, TEXT("This is a display"));
//	FString Log = TEXT("Hello World"); 
//	UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);	
//	UE_LOG(LogTemp, Error, TEXT("%p"), &Log);
//	
//	FString* LogPtr = &Log;
//	UE_LOG(LogTemp, Warning, TEXT("%s"), **LogPtr); // Hello World
//	UE_LOG(LogTemp, Error, TEXT("%p"), &LogPtr); // memoryaddress for logPtr
//	UE_LOG(LogTemp, Error, TEXT("%p"), &(*LogPtr)); // value is the memory address for Log
	
	 // Challenge
	// 1. create a variable to store the objects name. 
	// 2. Output the name of the object to the console in your log
	AActor* Actor = GetOwner();
	// get the FVector representation of the Actors location
	FVector LocationVector = Actor->GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("%s"), *LocationVector.ToString());

	// Don't forget the overload operator '*'
	UE_LOG(LogTemp, Error, TEXT("%s"), *Actor->GetName());

	// same thing, except with Ftransform
	FTransform Transform = Actor->GetTransform();
	FVector TransformFVector = Transform.GetLocation(); // Temp Function for easy conversion
	UE_LOG(LogTemp, Display, TEXT("%s"), *TransformFVector.ToString());
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

