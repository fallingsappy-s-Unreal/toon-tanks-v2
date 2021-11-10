// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Rotate);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation(0);
	DeltaLocation.X = Value;
	
	AddActorLocalOffset(DeltaLocation * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed);
}

void ATank::Rotate(float Value)
{
	FRotator DeltaRotation(0);
	DeltaRotation.Yaw = Value;
	
	AddActorLocalRotation(DeltaRotation * UGameplayStatics::GetWorldDeltaSeconds(this) * RotationSpeed);
}
