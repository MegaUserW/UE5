// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "TankPawn.generated.h"

//class UStaticMeshComponent;
//class UCameraComponent;
//class USpringArmComponent;
class ATankPlayerController;
//class ACannon;


UCLASS()
class MYTANKGAME_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupCannon();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Component")
		UStaticMeshComponent* BodyMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Component")
		UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Component")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Component")
		USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Movement")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Movement")
		float TankRotation = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank Movement")
		float InterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret Movement")
		float TurretRotationInterpolationKey = 0.5f;
	
	UPROPERTY()
		ATankPlayerController* TankController;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY()
		ACannon* Cannon;

	float TargetForwardAxisValue = 0.0f;
	float TargetRightAxisValue = 0.0f;
public:
	UFUNCTION()
		void Fire();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveForwardTankPawn(float DeltaTime);
	void MoveRightTankPawn(float DeltaTime);
};
