// Copyright @ 2021 DL Future Game Lab

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerBox.h"
#include "DoorBehavior.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UDoorBehavior : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorBehavior();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(Blueprintcallable)
	void ToggleDoor(bool IsOpen);
	UFUNCTION(Blueprintcallable)
	void OpenDoor();
	UFUNCTION(Blueprintcallable)
	void CloseDoor();

private:
	UPROPERTY(EditAnywhere)
	bool IsDoorOpen = false;
	UPROPERTY(EditAnywhere)
	float DoorOpenRange = 90.0f;
	UPROPERTY(EditAnywhere)
	float DoorSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.0f;
	UPROPERTY(EditAnywhere)
	ATriggerBox * PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
	float ActivationMass = 100.0f;
	
	bool InAction = false;
	float LerpPercent = 0.0f;
	AActor* CompOwner = nullptr;
	float InitialYaw;
	float TargetYaw;
	float DoorLastOpened = 0.0f;
	UPROPERTY()
	UAudioComponent* DoorSound = nullptr;
	void InitializeDoor();
	void DoorActions(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
};
