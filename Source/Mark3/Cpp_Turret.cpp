// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Containers/UnrealString.h"
#include "Cpp_Turret.h"

// Sets default values
ACpp_Turret::ACpp_Turret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TArray<AActor*> childActors;
	//GetAllChildActors(childActors);
	//barrelMesh = childActors[0];
}

// Called when the game starts or when spawned
void ACpp_Turret::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACpp_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugRay(GetWorld(), barrelMesh->GetComponentLocation(), barrelMesh->GetForwardVector() * 500, FColor::Red);
	DrawDebugRay(GetWorld(), GetActorLocation(), GetActorForwardVector() * 500, FColor::Orange);
	DrawDebugLine(GetWorld(), GetActorLocation(), target->GetActorLocation(), FColor::Black);
	DrawDebugLine(GetWorld(), barrelMesh->GetComponentLocation(), target->GetActorLocation(), FColor::Purple);
	FVector vecToTarget = target->GetActorLocation() - GetActorLocation();
	//FVector vecToTargetProj = FVector::VectorPlaneProject(vecToTarget, FVector::UpVector);
	FVector vecToTargetProj = FVector::VectorPlaneProject(vecToTarget, GetActorUpVector());
	FVector vecToTargetB = target->GetActorLocation() - barrelMesh->GetComponentLocation();
	FVector vecToTargetProjB = FVector::VectorPlaneProject(vecToTargetB, barrelMesh->GetRightVector());
	DrawDebugLine(GetWorld(), GetActorLocation(), vecToTargetProj + GetActorLocation(), FColor::Blue);
	DrawDebugLine(GetWorld(), barrelMesh->GetComponentLocation(), vecToTargetProjB + barrelMesh->GetComponentLocation(), FColor::Yellow);
	DrawDebugRay(GetWorld(), barrelMesh->GetComponentLocation(), vecToTargetProj * 1, FColor::Green);

	DrawDebugRay(GetWorld(), GetActorLocation(), vecToTarget * 0.5F, FColor::Cyan);
	DrawDebugRay(GetWorld(), barrelMesh->GetComponentLocation(), vecToTargetB * 0.5F, FColor::Magenta);

	FVector testVec = FVector::VectorPlaneProject(barrelMesh->GetForwardVector(), GetActorUpVector());
	//UE_LOG(LogTemp, Warning, TEXT("testVec: (%f,%f,%f)"), testVec.X, testVec.Y, testVec.Z);
	DrawDebugRay(GetWorld(), GetActorLocation(), testVec * 1000.0F, FColor::Red);

	float angle = SignedAngleRad(GetActorForwardVector(), vecToTarget, GetActorUpVector());
	float angleB = SignedAngleRad(barrelMesh->GetForwardVector(), vecToTargetB, barrelMesh->GetRightVector());

	FQuat qCurrent(FVector::UpVector, 0.0F);
	FQuat qGoal(FVector::UpVector, angle);

	//FQuat qCurrentB(barrelMesh->GetRightVector(), 0.0F);
	//FQuat qGoalB(barrelMesh->GetRightVector(), angleB);

	FQuat qCurrentB(FVector::RightVector, 0.0F);
	FQuat qGoalB(FVector::RightVector, angleB);

	//UE_LOG(LogTemp, Warning, TEXT("qCurrent: (%f,%f,%f,%f)"), qCurrent.W, qCurrent.X, qCurrent.Y, qCurrent.Z);
	//UE_LOG(LogTemp, Warning, TEXT("qGoal: (%f,%f,%f,%f)"), qGoal.W, qGoal.X, qGoal.Y, qGoal.Z);
	//UE_LOG(LogTemp, Warning, TEXT("qGoal: (%f,%f,%f,%f)"), qGoalB.W, qGoalB.X, qGoalB.Y, qGoalB.Z);

	FQuat qDelta = FQuat::Slerp(qCurrent, qGoal, yawSpeed * DeltaTime);
	FQuat qDeltaB = FQuat::Slerp(qCurrentB, qGoalB, pitchSpeed * DeltaTime);

	if (enableYaw)
	{
		//AddActorWorldRotation(qDelta);
		AddActorLocalRotation(qDelta);
	}
	if (enablePitch)
	{
		FRotator r = barrelMesh->GetComponentRotation();
		UE_LOG(LogTemp, Log, TEXT("Test %f %f %f"), r.Pitch, r.Yaw, r.Roll);
		//barrelMesh->AddActorWorldRotation(qDeltaB);
		barrelMesh->AddLocalRotation(qDeltaB);

		UE_LOG(LogTemp, Log, TEXT("TestAfter %f %f %f"), r.Pitch, r.Yaw, r.Roll);

	}

}

// Helper function, for drawing debug line, be specifying point of origin, and a direction with length.
void ACpp_Turret::DrawDebugRay
(
	const UWorld* InWorld,
	const FVector& Origin,
	const FVector& Direction,
	const FColor& Color,
	bool bPersistentLines,
	float LifeTime,
	uint8 DepthPriority,
	float Thickness
) const
{
	DrawDebugLine(InWorld, Origin, Origin + Direction, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
}

float ACpp_Turret::AngleRad(FVector V1, FVector V2) const
{
	/*float unused;
	float angle;*/
	V1.Normalize();
	V2.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("V1: (%f,%f,%f)  V2:(%f,%f,%f)"), V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);
	//GetSinCos(unused, angle, FVector::DotProduct(V1, V2));
	return acosf(FVector::DotProduct(V1, V2));
}

float ACpp_Turret::Angle(FVector V1, FVector V2) const
{
	/*float unused;
	float angle;*/
	V1.Normalize();
	V2.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("V1: (%f,%f,%f)  V2:(%f,%f,%f)"), V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);
	//GetSinCos(unused, angle, FVector::DotProduct(V1, V2));
	return acosf(FVector::DotProduct(V1, V2)) * (180.0f / PI);
}

float ACpp_Turret::SignedAngleRad(FVector V1, FVector V2, FVector NormalVector) const
{
	V1 = FVector::VectorPlaneProject(V1, NormalVector);
	V2 = FVector::VectorPlaneProject(V2, NormalVector);
	V1.Normalize();
	V2.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("V1: (%f,%f,%f)  V2:(%f,%f,%f)"), V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);

	float angle = acosf(FVector::DotProduct(V1, V2));

	FVector cross = FVector::CrossProduct(V1, V2);
	cross.Normalize();
	if (FVector::DotProduct(cross, NormalVector) < 0)
	{
		angle = -angle;
	}


	//UE_LOG(LogTemp, Warning, TEXT("NormalVector: (%f,%f,%f)  cross:(%f,%f,%f)"), NormalVector.X, NormalVector.Y, NormalVector.Z, cross.X, cross.Y, cross.Z);

	return angle;
}

float ACpp_Turret::SignedAngle(FVector V1, FVector V2, FVector NormalVector) const
{
	V1 = FVector::VectorPlaneProject(V1, NormalVector);
	V2 = FVector::VectorPlaneProject(V2, NormalVector);
	V1.Normalize();
	V2.Normalize();

	//UE_LOG(LogTemp, Warning, TEXT("V1: (%f,%f,%f)  V2:(%f,%f,%f)"), V1.X, V1.Y, V1.Z, V2.X, V2.Y, V2.Z);

	float angle = acosf(FVector::DotProduct(V1, V2)) * (180.0f / PI);

	FVector cross = FVector::CrossProduct(V1, V2);
	cross.Normalize();
	if (FVector::DotProduct(cross, NormalVector) < 0)
	{
		angle = -angle;
	}


	//UE_LOG(LogTemp, Warning, TEXT("NormalVector: (%f,%f,%f)  cross:(%f,%f,%f)"), NormalVector.X, NormalVector.Y, NormalVector.Z, cross.X, cross.Y, cross.Z);

	return angle;
}

void ACpp_Turret::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing!"));
	TriggerFire();
	//GetWorld()->SpawnActor<AStaticMeshActor>(Bullet_Blueprint_C, barrelMesh->GetComponentLocation(), barrelMesh->GetActorRotation());
}

