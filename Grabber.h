// Copyright Sebastian Gumula 2019

#pragma once
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	// Grab an object
	void Grab();
	// Release an object
	void Release();
	// Find attached physics handle
	void FindPhysicsHandleController();
	// Setup an input component
	void SetupInputComponent();
	// Return hit for first physics body reach
	const FHitResult GetFirstPhysicsBodyInReach();
	// Returns starting point of reach line
	FVector GetReachLineStart();
	// Returns current end of reach line
	FVector GetReachLineEnd();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
