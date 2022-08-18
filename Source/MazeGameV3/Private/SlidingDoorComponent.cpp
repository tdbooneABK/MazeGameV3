// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoorComponent.h"

// Sets default values for this component's properties
USlidingDoorComponent::USlidingDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlidingDoorComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USlidingDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Opening) {
		RemainingMoveTime -= DeltaTime;
		const float TimeRatio = FMath::Clamp(RemainingMoveTime / TimeToMove, 0.0f, 1.0f);
		const FVector CurrentPosition = FMath::Lerp(FinalPosition, StartPosition, TimeRatio);
		GetOwner()->SetActorLocation(CurrentPosition);
	}
}

void USlidingDoorComponent::Open()
{
	Opening = true;
	RemainingMoveTime = TimeToMove;
	StartPosition = GetOwner()->GetActorLocation();
	FinalPosition = GetOwner()->GetActorLocation() + OpenTranslation;
}
