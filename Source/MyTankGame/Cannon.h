// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Cannon.generated.h"

UCLASS()
class MYTANKGAME_API ACannon : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		ECannonType Type = ECannonType::FireProjectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int CountAmmunition = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int SpecialNum = 3;
	FTimerHandle ReloadTimerHandle;
	bool ReadyToFire = true;
	bool ReadyToSpecialFire = true;
	bool specialStart = false;
	int currentSpecial = 0;


public:	
	// Sets default values for this actor's properties
	ACannon();
	void Fire();
	void FireSpecial();
	bool IsReadyToFire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Reload();
	void ReloadSpecial();

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
