// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFrameWork/Actor.h"
#include "GameFrameWork/PlayerController.h"
#include "Engine/World.h"
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

	// When the game is playing, Unreal will search the world for the defaultPawn and assign the OpenDoor.ActorTriggeringOpenDoor option to that pawn 
	ActorTriggeringOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ActorTriggeringOpenDoor)
	{
		UE_LOG(LogTemp, Error, TEXT("The Actor %s, is assigned to the OpenDoor Component, which requires a AActor assigned to option ActorTriggeringOpenDoor under the OpenDoor Property"))
	}

	if (!PressurePlate)
	{
		// ActorName has the open door component, but no pressureplate set
		UE_LOG(LogTemp, Error, TEXT("The Actor %s, is assigned the OpenDoor Component, which requires a TriggerVolume PressurePlate to be assigned."), *GetOwner()->GetActorLabel())
	}
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
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaT * OpenLerpAlpha);
	FRotator DoorRotator = GetOwner()->GetActorRotation();
	DoorRotator.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotator);
	UE_LOG(LogTemp, Error, TEXT("the Lerp Rotation is %f"), DoorRotator.Yaw);	
}

void UOpenDoor::CloseDoor(float DeltaT) {
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaT * CloseLerpAlpha);
	FRotator DoorRotator = GetOwner()->GetActorRotation();
	DoorRotator.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotator);
	UE_LOG(LogTemp, Error, TEXT("the Lerp Rotation the close the door is %f"), DoorRotator.Yaw);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("The DT is %f and the CTD is %f"), DoorOpenedTime, CloseDoorLatency);
	// How do we protect against dereferencing a null pointer?
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorTriggeringOpenDoor))
	{
		OpenDoor(DeltaTime);
		// set the time the door is opened
		DoorOpenedTime = GetWorld()->GetRealTimeSeconds();
	}
	// Once the Door has been Open longet than the CloseDoorLatency, let the door close.
	// The moment you leave the trigger, you have two seconds until the door closes
	else if (GetWorld()->GetTimeSeconds() - DoorOpenedTime > CloseDoorLatency)
	{
		// prevents excessive need to always compute the door close every frame, only if the door is open it needs to close
		if (CurrentYaw != InitialYaw) 
		{
			CloseDoor(DeltaTime);
		}
	}
	
	
//	if (!PressurePlate->IsOverlappingActor(ActorTriggeringOpenDoor))
//	{
//		CloseDoor(DeltaTime);
//		isPrevOverlapping = false;
//	}

} 