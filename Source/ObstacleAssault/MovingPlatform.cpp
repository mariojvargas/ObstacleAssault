// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		ReversePlatformDirection();
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MaxMoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartLocation, GetActorLocation());
}

void AMovingPlatform::ReversePlatformDirection()
{
	FVector MoveDirection = PlatformVelocity.GetSafeNormal();
	StartLocation = StartLocation +  MoveDirection * MaxMoveDistance;
	SetActorLocation(StartLocation);

	PlatformVelocity = -PlatformVelocity;
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}