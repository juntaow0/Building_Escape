// Copyright @ 2021 DL Future Game Lab


#include "DoorBehavior.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorBehavior::UDoorBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CompOwner = GetOwner();
}

// Called when the game starts
void UDoorBehavior::BeginPlay()
{
	Super::BeginPlay();
	//InitializeDoor();
}

// Called every frame
void UDoorBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"),CompOwner->GetActorRotation().Yaw);
	float CurrentYaw = CompOwner->GetActorRotation().Yaw;
	FRotator OpenDoor(0.0f,0.0f,0.0f);
	OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw,TargetYaw,DeltaTime,DoorSpeed);
	CompOwner->SetActorRotation(OpenDoor);
}

// open or close door
void UDoorBehavior::ToggleDoor(bool IsOpen){
	if (IsOpen==IsDoorOpen){
		return;
	}
	auto DoorRotation = CompOwner->GetActorRotation();
	int32 Direction = IsOpen? -1:1;
	DoorRotation.Yaw += 90.0f*Direction;
	CompOwner->SetActorRotation(DoorRotation);
	IsDoorOpen = IsOpen;
}

void UDoorBehavior::InitializeDoor(){
	if (IsDoorOpen){
		auto DoorRotation = CompOwner->GetActorRotation();
		DoorRotation.Yaw += 90.0f;
		CompOwner->SetActorRotation(DoorRotation);
	}
}


	


