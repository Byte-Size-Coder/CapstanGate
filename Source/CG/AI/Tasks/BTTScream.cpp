// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BTTScream.h"

////////////////////////Prototype - Not used In Game ///////////////////////////////////////////////////////////

UBTTScream::UBTTScream(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTScream::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// If there is no world, the execution fails.
	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	// Get a reference to the player.
	AEric* Player = Cast<AEric>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Player")));

	// Get a reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("SelfActor")));

	FVector EnemyLocation = Enemy->GetActorLocation();

	FCollisionQueryParams TraceParams(FName(TEXT("ScreamTrace")), true, Enemy);

	TArray<FOverlapResult> Hits;
	GetWorld()->OverlapMultiByChannel(Hits, EnemyLocation, FQuat::Identity, COLLISION_ENEMY, FCollisionShape::MakeSphere(2000.0f), TraceParams);

	// Go through all the objects that it hits.
	for (FOverlapResult Result : Hits)
	{
		// Get reference to the enemy and enemy controller.
		AEnemy* AlertEnemy = Cast<AEnemy>(Result.Actor.Get());
		AEnemyController* AlertEnemyController = Cast<AEnemyController>(AlertEnemy->GetController());

		if (!AlertEnemy->CanSeePlayer())
		{
			

			UNavigationSystem* Nav = GetWorld()->GetNavigationSystem();

			FVector AlertEnemyLocation = AlertEnemy->GetActorLocation();

			AlertEnemy->GetCharacterMovement()->MaxWalkSpeed = AlertEnemy->GetEngagedSpeed();

			FVector RunPoint;

			bool bAdvance = false;

			int Count = 0;

			while (!bAdvance && Count <= 10)
			{
				RunPoint.X = EnemyLocation.X + FMath::FRandRange(-100, 100);
				RunPoint.Y = EnemyLocation.Y + FMath::FRandRange(-100, 100);
				RunPoint.Z = EnemyLocation.Z;

				if (Nav)
				{
					FPathFindingQuery QueryParams;
					QueryParams.StartLocation = EnemyLocation;
					QueryParams.EndLocation = RunPoint;
					QueryParams.NavData = Nav->GetMainNavData();
					QueryParams.Owner = Enemy;
					QueryParams.SetAllowPartialPaths(false);

					if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
					{
						UE_LOG(LogTemp, Warning, TEXT("VALID TRACK OF PLAYER CLOSE"));
						AlertEnemy->SetMemoryLocation(RunPoint);
						bAdvance = true;
						Enemy->SetSawPlayer(false);

						AlertEnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), Player);
						AlertEnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Memory"), AlertEnemy->PlayerMemory);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("INVALID TRACK OF PLAYER CLOSE"));
						Count++;
					}
				}
			}
		}

	}

	return EBTNodeResult::Succeeded;
}