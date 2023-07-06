// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <MyTankGame/TankPawn.h>
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYTANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		ATankPawn* TankPawn;

	UPROPERTY()
		FVector MousePos;

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;
	FVector GetMousePos();


protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Fire();
	void FireSpecial();

};

