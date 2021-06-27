// Copyright @ 2021 DL Future Game Lab

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorBehavior.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UDoorBehavior : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorBehavior();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	bool IsDoorOpen = false;

	UPROPERTY(EditAnywhere)
	float DoorSpeed = 2.0f;

	UPROPERTY(VisibleAnywhere)
	AActor* CompOwner;

	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.0f;;

	UFUNCTION(Blueprintcallable)
	void ToggleDoor(bool IsOpen);
	void InitializeDoor();
};
