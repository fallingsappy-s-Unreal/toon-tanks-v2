// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleDestruction() override;
	
protected:
	virtual void BeginPlay() override;

private:
	class ATank* PlayerTank;

	UPROPERTY(EditAnywhere, Category = "Combat", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange() const;
};
