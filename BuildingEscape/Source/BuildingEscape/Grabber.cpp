// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Math/Color.h"
#include "Grabber.h"

// define a Macro OUT that will indicate to us that a function is updating the value passed by reference
// on Compile, OUT will be replaced with nothing, and will therefore be removed from code on compile.
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();
	UE_LOG(LogTemp, Error, TEXT("Grabber has attached to %s, and is report for duty!"), *Owner->GetName());

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("The physics handle is missing from the actor: %s"), *Owner->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("The physics handle is attached to the actor %s and is reporting for duty"), *Owner->GetName());
	}
		
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get playersviewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	APlayerController* PlayerCon = GetWorld()->GetFirstPlayerController();
	
	// I think we are passing by reference when using the &
	PlayerCon->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

//	UE_LOG(LogTemp,
//		Warning,
//		TEXT("the actor's location is %s and the rotation is %s"),
//		*PlayerViewPointLocation.ToString(),
//		*PlayerViewPointRotation.ToString()
//	);
	

	// Draw a line vector
	FVector LineTraceEnd = PlayerViewPointLocation + (Reach * PlayerViewPointRotation.Vector());
	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor::MakeFromColorTemperature(200.F),
		false,
		0.F,
		(uint8)0U,
		5.F
	);

	// Params for LineTrace...Type(..) function
	FHitResult Hit = FHitResult();
	FVector Start = PlayerViewPointLocation;
	FVector End = LineTraceEnd;
	FCollisionObjectQueryParams ObjectQueryParams = ECollisionChannel::ECC_PhysicsBody;

	// Params for TraceParams
	FName InTraceTag = FName(TEXT("")); // Leave it blank
	bool bInTraceComplex = false; // we do not want to use complexes in our traces
	const AActor * InIgnoreActor = GetOwner(); // Ignore current owner which the trace intersects with given the starting point is the center of the sphere
	FCollisionQueryParams TraceParams(InTraceTag, bInTraceComplex, InIgnoreActor);

	// Log out anything we are intersecting with while using our raycast
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, Start, End, ObjectQueryParams, TraceParams);
	
	// See what it hits
//	if (Hit.Item != NULL) {
//		UE_LOG(LogTemp, Warning, TEXT("The object hit is %s"), *Hit.GetActor()->GetName());
//	}
	// preferably
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("The object hit is %s"), *(ActorHit->GetName()));
	}
}

