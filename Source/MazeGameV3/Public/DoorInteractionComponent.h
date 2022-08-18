// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEGAMEV3_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;

	FRotator OriginalRotation = FRotator::ZeroRotator;
	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	float TimeAloneToClose = 1.5f;
	float TimeSpentAlone = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerBase* DoorOpenTrigger;

	UPROPERTY(EditAnywhere)
	ATriggerBase* DoorOpenOutwardTrigger;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve DoorOperCurve;

	UPROPERTY(EditAnywhere)
	bool TwoWayRotation = false;

	UPROPERTY(EditAnywhere)
	bool CloseWhenAlone = false;

	bool IsOpen = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
