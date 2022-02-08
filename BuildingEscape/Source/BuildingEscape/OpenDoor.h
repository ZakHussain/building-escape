// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h" // Must go at the bottom always

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
private: 
	float InitialYaw;
	float TargetYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere) 
	float Open = 90.f;
	
	UPROPERTY(EditAnywhere) 
	float Close = -90.f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorTriggeringOpenDoor;
	
	UPROPERTY(EditAnywhere)
	float OpenLerpAlpha = 1.f; // higher value -> faster closing
	
	UPROPERTY(EditAnywhere)
	float CloseLerpAlpha = 2.f; 
	// track time
	float DoorOpenedTime = 0.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorLatency = 2.f; // time before door starts to close once pawn has left the TriggerVolume
};
