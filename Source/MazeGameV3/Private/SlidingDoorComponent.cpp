// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoorComponent.h"
#include "Engine/TriggerBase.h"

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
	OriginalPosition = GetOwner()->GetActorLocation();
}


// Called every frame
void USlidingDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool PlayerOnTrigger = false;

	if (DoorOpenTrigger && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController()) {
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && DoorOpenTrigger->IsOverlappingActor(PlayerPawn)) {
			Open();
			PlayerOnTrigger = true;
		}
	}

	if (Opening || Closing) {
		RemainingMoveTime -= DeltaTime;
		const float TimeRatio = FMath::Clamp(RemainingMoveTime / TimeToMove, 0.0f, 1.0f);
		const FVector CurrentPosition = FMath::Lerp(FinalPosition, StartPosition, TimeRatio);
		GetOwner()->SetActorLocation(CurrentPosition);
	}

	if (CloseAfterTime > 0.0f && !PlayerOnTrigger && TimeUntilClose > 0.0f) {
		TimeUntilClose -= DeltaTime;
		if (TimeUntilClose <= 0.0f) {
			Close();
		}
	}
	else {
		TimeUntilClose = CloseAfterTime;
	}
}

void USlidingDoorComponent::Open()
{
	if (!Opening) {
		Opening = true;
		Closing = false;
		RemainingMoveTime = TimeToMove;
		StartPosition = GetOwner()->GetActorLocation();
		FinalPosition = GetOwner()->GetActorLocation() + OpenTranslation;
	}
}

void USlidingDoorComponent::Close()
{
	if (!Closing) {
		Closing = true;
		Opening = false;
		RemainingMoveTime = TimeToMove;
		StartPosition = GetOwner()->GetActorLocation();
		FinalPosition = OriginalPosition;
	}
}
