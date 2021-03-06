// Copyright @ 2021 DL Future Game Lab

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float GrabDistance = 200.f;
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle=nullptr;
	UPROPERTY()
	UInputComponent* InputComponent=nullptr;
	void Grab();
	void Release();
	FHitResult GetFirstPhysicsBodyInReach() const;
	void SetupInput();
	FVector GetLineTraceEnd() const;
	FVector GetPlayerViewPointPos() const;
	UPROPERTY()
	UWorld* CurrentWorld = nullptr;
	UPROPERTY()
	APlayerController* FirstPlayerController = nullptr;

	
};
