// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "Engine/TriggerBase.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetOwner()->GetActorRotation();
	CurrentRotationTime = TimeToRotate;
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool PlayerOnTrigger = false;
	if (DoorOpenTrigger && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController()) {
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && DoorOpenTrigger->IsOverlappingActor(PlayerPawn)) {
			PlayerOnTrigger = true;
			if ((!IsOpen) && CurrentRotationTime >= TimeToRotate) {
				StartRotation = GetOwner()->GetActorRotation();
				FinalRotation = OriginalRotation + DesiredRotation;
				CurrentRotationTime = 0.0f;
				IsOpen = true;
			}
		}
		else if (PlayerPawn && TwoWayRotation && DoorOpenOutwardTrigger && DoorOpenOutwardTrigger->IsOverlappingActor(PlayerPawn))
		{
			PlayerOnTrigger = true;
			if ((!IsOpen) && CurrentRotationTime >= TimeToRotate) {
				StartRotation = GetOwner()->GetActorRotation();
				FinalRotation = OriginalRotation - DesiredRotation;
				CurrentRotationTime = 0.0f;
				IsOpen = true;
			}
		}
	}

	if (!PlayerOnTrigger) {
		TimeSpentAlone += DeltaTime;
	}
	else {
		TimeSpentAlone = 0.0f;
	}

	if (IsOpen && TimeSpentAlone > TimeAloneToClose) {
		StartRotation = GetOwner()->GetActorRotation();
		FinalRotation = OriginalRotation;
		CurrentRotationTime = 0.0f;
		IsOpen = false;
	}

	if (CurrentRotationTime < TimeToRotate) {
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = DoorOperCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
}

