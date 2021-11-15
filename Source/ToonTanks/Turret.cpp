// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (InFireRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::CheckFireCondition()
{
	if (PlayerTank == nullptr || !PlayerTank->bAlive)
	{
		return;
	}
	
	if (InFireRange())
	{
		Fire();
	}
}

bool ATurret::InFireRange() const
{
	if (PlayerTank)
	{
		const float Distance = FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());

		return Distance <= FireRange;
	}

	return false;
}
