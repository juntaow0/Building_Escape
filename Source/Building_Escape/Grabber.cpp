// Copyright @ 2021 DL Future Game Lab
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber.h"

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
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle){
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Missing for %s"),*GetOwner()->GetName());
	}
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()* GrabDistance;
	
	DrawDebugLine(GetWorld(),PlayerViewPointLocation,LineTraceEnd, FColor(0,255,0), false, 0.f, 0,5.f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	bool LineHit = GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	if (LineHit && Hit.GetActor()){
		FString HitName = Hit.GetActor()->GetName();
		UE_LOG(LogTemp,Warning, TEXT("Line trace has hit %s"), *HitName);
	}
}

