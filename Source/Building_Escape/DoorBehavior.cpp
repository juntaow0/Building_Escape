// Copyright @ 2021 DL Future Game Lab


#include "DoorBehavior.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

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
	if (!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("%s has DoorBehavior, but no Trigger set"),*CompOwner->GetName());
	}
	FindAudioComponent();
	InitializeDoor();
	//FScriptDelegate Delegate1;
	//FScriptDelegate Delegate2;
	//Delegate1.BindUFunction(this, "OpenDoor");
	//Delegate2.BindUFunction(this, "CloseDoor");
	//PressurePlate->OnActorBeginOverlap.Add(Delegate1);
	//PressurePlate->OnActorEndOverlap.Add(Delegate2);
}

// Called every frame
void UDoorBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	 if (PressurePlate && TotalMassOfActors()>=ActivationMass){
	 	ToggleDoor(true);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	 }else{
		 if (GetWorld()->GetTimeSeconds()-DoorCloseDelay>DoorLastOpened){
			 ToggleDoor(false);
		 }
	 }
	DoorActions(DeltaTime);
}

// open or close door
void UDoorBehavior::ToggleDoor(bool IsOpen){
	if (IsOpen==IsDoorOpen){
		return;
	}
	if (InAction){
		return;
	}
	DoorSound->Play();
	FRotator DoorRotation = CompOwner->GetActorRotation();
	TargetYaw =  DoorRotation.Yaw + DoorOpenRange* (IsOpen? 1:-1);
	InitialYaw = DoorRotation.Yaw;
	IsDoorOpen = IsOpen;
	InAction = true;
}

void UDoorBehavior::OpenDoor(){
	ToggleDoor(true);
}

void UDoorBehavior::CloseDoor(){
	ToggleDoor(false);
}

void UDoorBehavior::InitializeDoor(){
	if (IsDoorOpen){
		FRotator DoorRotation = CompOwner->GetActorRotation();
		TargetYaw =  DoorRotation.Yaw + DoorOpenRange;
		InitialYaw = DoorRotation.Yaw;
		InAction = true;
	}
}

void UDoorBehavior::DoorActions(float DeltaTime){
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

float UDoorBehavior::TotalMassOfActors() const{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) return TotalMass;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (auto Actor:OverlappingActors){
		TotalMass+=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

void UDoorBehavior::FindAudioComponent(){
	DoorSound = CompOwner->FindComponentByClass<UAudioComponent>();
	if (!DoorSound){
		UE_LOG(LogTemp, Error, TEXT("No audio component found for %s"),*CompOwner->GetName());
	}else{
		DoorSound->bAutoActivate=false;
	}
}


