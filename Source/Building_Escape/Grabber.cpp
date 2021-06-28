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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	CurrentWorld = GetWorld();
	FirstPlayerController = CurrentWorld->GetFirstPlayerController();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle){
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Missing for %s"),*GetOwner()->GetName());
	}
	SetupInput();
}
 
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent){
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

void UGrabber::Grab(){
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit){
		FVector LineTraceEnd = GetLineTraceEnd();
		UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
		if (!PhysicsHandle) return;
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
}

void UGrabber::Release(){
	if (!PhysicsHandle) return;
	PhysicsHandle->ReleaseComponent();
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	CurrentWorld->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerViewPointPos(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}

void UGrabber::SetupInput(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent){
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

FVector UGrabber::GetLineTraceEnd() const{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FirstPlayerController->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector()* GrabDistance;
}

FVector UGrabber::GetPlayerViewPointPos() const{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FirstPlayerController->GetPlayerViewPoint(OUT PlayerViewPointLocation, PlayerViewPointRotation);
	return PlayerViewPointLocation;
}