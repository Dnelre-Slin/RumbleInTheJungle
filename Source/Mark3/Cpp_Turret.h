// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Cpp_Turret.generated.h"

UCLASS(Blueprintable)
class MARK3_API ACpp_Turret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_Turret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Helper function, for drawing debug line, be specifying point of origin, and a direction with length.
	void DrawDebugRay
	(
		const UWorld* InWorld,
		const FVector& Origin,
		const FVector& Direction,
		const FColor& Color,
		bool bPersistentLines = false,
		float LifeTime = (-1.0F),
		uint8 DepthPriority = (uint8)'\0',
		float Thickness = (0.0F)
	) const;

	float AngleRad(FVector V1, FVector V2) const;
	float Angle(FVector V1, FVector V2) const;
	float SignedAngleRad(FVector V1, FVector V2, FVector NormalVector) const;
	float SignedAngle(FVector V1, FVector V2, FVector NormalVector) const;

	UFUNCTION(CallInEditor)
	void Fire();

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* barrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float yawSpeed = 1.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float pitchSpeed = 1.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool enableYaw = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool enablePitch = true;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UPROPERTY(EditAnywhere)
	//AStaticMeshActor* bulletSpawner = nullptr;

};
