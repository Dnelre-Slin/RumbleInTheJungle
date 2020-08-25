// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinionController.generated.h"

/**
 * 
 */
UCLASS()
class MARK3_API AMinionController : public AAIController
{
	GENERATED_BODY()

	
public:
	AMinionController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:

	void OnMoveCompleted(FAIRequestID RequestId, const FPathFollowingResult & Result) override;

	UFUNCTION(blueprintcallable)
	void OnSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* targetPosition;
};
