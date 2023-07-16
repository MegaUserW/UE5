// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "TankPawn.generated.h"

//class UStaticMeshComponent;
//class UCameraComponent;
//class USpringArmComponent;
class ATankPlayerController;
//class ACannon;


UCLASS()
class MYTANKGAME_API ATankPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
		TArray<FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params | Accurency")
		float MovementAccurency = 50;


	float TargetForwardAxisValue = 0.0f;
	float TargetRightAxisValue = 0.0f;


protected:
	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float DamageValue);

public:
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void FireSpecial();
	UFUNCTION()
		void TakeDamage(FDamageData DamageData);
	UFUNCTION()
		TArray<FVector> GetPatrollingPoints() { return PatrollingPoints; };
	UFUNCTION()
		float GetMovementAccurency() { return MovementAccurency; };
	UFUNCTION()
		FVector GetTurretForwardVector();
	UFUNCTION()
		void RotateTurretTo(FVector TargetPosition);



	FVector GetEyesPosition();
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveForwardTankPawn(float DeltaTime);
	void MoveRightTankPawn(float DeltaTime);
	void FireTank();
	void SetupCannon(TSubclassOf<ACannon> newCannon);
};
