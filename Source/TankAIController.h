#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class MYTANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATankAIController();
//protected:
//	UPROPERTY()
//		//	ATankPawn* TankPawn;
//		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
//		//	TArray<FVector> PatrollingPoints;
//		//int32 CurrentPatrolPointIndex = 0;
//		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
//		//	float MovementAccurency;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};