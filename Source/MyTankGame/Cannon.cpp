// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm =
		CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
		ProjectileSpawnPoint->SetupAttachment(Mesh);

}

void ACannon::Fire()
{

	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;
	if (Type == ECannonType::FireProjectile && CountAmmunition > 0)
	{
		GEngine->AddOnScreenDebugMessage(11, 1, FColor::Green, "Fire - projectile");
		FTransform projectileTransform(ProjectileSpawnPoint->GetComponentRotation(),
			ProjectileSpawnPoint->GetComponentLocation(), FVector(1));
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());

		if (projectile)
		{
			projectile->Start();
		}

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
		FHitResult hitResult;
		FCollisionQueryParams traceParams =
			FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;
		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end,
			ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false,
				0.5f, 0, 5);
			if (hitResult.GetActor())
			{
				hitResult.GetActor()->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,
		&ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToSpecialFire)
	{
		return;
	}
	ReadyToSpecialFire = false;
	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "FireSpecial - projectile");
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,
			&ACannon::Reload, 1 / FireRate, false);

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "FireSpecial - trace");
	}

}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
	ReadyToSpecialFire = true;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}

