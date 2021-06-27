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
	InitializeDoor();
}

// Called every frame
void UDoorBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!InAction){
		return;
	}
	FRotator CurrentRotation = CompOwner->GetActorRotation();
	if (LerpPercent>=1.0f){
		InAction = false;
		LerpPercent = 0.0f;
		CurrentRotation.Yaw = TargetYaw;
		CompOwner->SetActorRotation(CurrentRotation);
		UE_LOG(LogTemp, Warning, TEXT("Door Action Complete"));
		return;
	}
	LerpPercent += DoorSpeed*DeltaTime;
	CurrentRotation.Yaw = FMath::Lerp(InitialYaw,TargetYaw, LerpPercent);
	CompOwner->SetActorRotation(CurrentRotation);
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f, Lerp is: %f"),CurrentRotation.Yaw, LerpPercent);
}

// open or close door
void UDoorBehavior::ToggleDoor(bool IsOpen){
	if (IsOpen==IsDoorOpen){
		return;
	}
	if (InAction){
		return;
	}
	FRotator DoorRotation = CompOwner->GetActorRotation();
	TargetYaw =  DoorRotation.Yaw + 90.0f* (IsOpen? -1:1);
	InitialYaw = DoorRotation.Yaw;
	IsDoorOpen = IsOpen;
	InAction = true;
}

void UDoorBehavior::InitializeDoor(){
	if (IsDoorOpen){
		FRotator DoorRotation = CompOwner->GetActorRotation();
		TargetYaw =  DoorRotation.Yaw + 90.0f;
		InitialYaw = DoorRotation.Yaw;
		InAction = true;
	}
}


	


