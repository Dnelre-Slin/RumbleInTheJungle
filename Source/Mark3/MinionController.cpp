// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionController.h"

// Sets default values
AMinionController::AMinionController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//targetPosition = nullptr;
}

// Called when the game starts or when spawned
void AMinionController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMinionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (targetPosition != nullptr)
	//{
	//	FAIMoveRequest moveRequest(targetPosition);
	//	MoveTo(moveRequest);
	//}
}

void AMinionController::OnMoveCompleted(FAIRequestID RequestId, const FPathFollowingResult & Result)
{
	UE_LOG(LogTemp, Display, TEXT("Move completed"));
}

void AMinionController::OnSpawn()
{
	UE_LOG(LogTemp, Display, TEXT("Spawned!"));

	if (targetPosition != nullptr)
	{
		FAIMoveRequest moveRequest(targetPosition);
		MoveTo(moveRequest);
	}
}