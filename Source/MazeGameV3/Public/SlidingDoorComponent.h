// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlidingDoorComponent.generated.h"

class ATriggerBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class MAZEGAMEV3_API USlidingDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlidingDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float TimeToMove = 1.0f;

	UPROPERTY(EditAnywhere)
	float CloseAfterTime = 0.0f;
	float TimeUntilClose = 0.0f;

	UPROPERTY(EditAnywhere)
	FVector OpenTranslation;
	FVector StartPosition;
	FVector FinalPosition;
	FVector OriginalPosition;

	float RemainingMoveTime = 0.0f;
	
	bool Opening = false;
	bool Closing = false;

	UPROPERTY(EditAnywhere)
	ATriggerBase* DoorOpenTrigger;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();
};
