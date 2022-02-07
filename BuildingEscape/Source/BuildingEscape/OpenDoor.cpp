// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFrameWork/Actor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();
	FRotator CurRotator = Owner->GetActorRotation();
	InitialYaw = CurRotator.Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + Open;
	//	AActor* Owner = GetOwner();
	//	FRotator Rotation = Owner->GetActorRotation();
	//	UE_LOG(LogTemp, Error, TEXT("The Rotation is %s"), *Rotation.ToString());
	//
	//	Rotation.Yaw = 90.f; 
	//	Owner->SetActorRotation(Rotation);

	// Way two would have been: 
	//FRotator Rotator(0.f, 90.f, 0.f); 
	// FRotator Rotator = {0.f, 90.f, 0.f}
	//GetOwner()->SetActorRotation(Rotator);
	
	// Get the current value of the doors yaw rotation
	// Take the current position and add 90  to get the target Value
	// 
}

void UOpenDoor::OpenDoor(float DeltaT) {
	// Deltatime * Alpha will decouple the object from using the frameRate, and 
	// keep the values in-line with time. 
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaT * Alpha);
	FRotator DoorRotator = GetOwner()->GetActorRotation();
	DoorRotator.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotator);
	UE_LOG(LogTemp, Error, TEXT("the Lerp Rotation is %f"), DoorRotator.Yaw);	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// How do we protect against dereferencing a null pointer?
	if (PressurePlate->IsOverlappingActor(ActorTriggeringOpenDoor)) 
	{
		OpenDoor(DeltaTime);
	}
} 