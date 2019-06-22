// Copyright Sebastian Gumula 2019

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Engine/Classes/Engine/World.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay(); 
	Door = GetOwner();

	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
	// ...
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame:
	if (GetTotalMassOfActorsOnPlate() > 30.f) 
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

}
float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	TArray<AActor*> OverlappingActors;
	float TotalMass = 0.f;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
