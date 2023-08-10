// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BTTLookAround.h"


UBTTLookAround::UBTTLookAround(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTLookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// If there is no world, the execution fails.
	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	// Get a reference to the player.
	AEric* Player = Cast<AEric>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Player")));

	// Get player location.
	FVector PlayerLocation = Player->GetActorLocation();

	// Get a reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("SelfActor")));

	// Get enemy location.
	FVector EnemyLocation = Enemy->GetActorLocation();

	// Get the Memorylocation reference from the blackboard.
	AMemoryLocation* Memory = Cast<AMemoryLocation>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Memory")));

	FVector MemoryLocation = Memory->GetActorLocation();

	UNavigationSystem* Nav = GetWorld()->GetNavigationSystem();

	// Get the distance from the enemy to player.
	float Dist = FVector::Dist(EnemyLocation, PlayerLocation);
	
	// Set the enemy's speed. Execution is a success.
	Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetPatrolSpeed();

	// Create necessary variables for loop
	bool bAdvance = false;

	int Count = 0;

	// Continue loop if advance remains false or the counter is less then 10.
	while (!bAdvance && Count <= 10)
	{

		// Create a vector (LookPoint) and set its locations to a random location around the enemy.
		FVector LookPoint = FVector::ZeroVector;
		LookPoint.X = EnemyLocation.X + FMath::FRandRange(-500, 500);
		LookPoint.Y = EnemyLocation.Y + FMath::FRandRange(-500, 500);
		LookPoint.Z = EnemyLocation.Z;

		if (Nav)
		{
			// Create a path findy query and set its parameters.
			FPathFindingQuery QueryParams;
			QueryParams.StartLocation = EnemyLocation;
			QueryParams.EndLocation = LookPoint;
			QueryParams.NavData = Nav->GetMainNavData();
			QueryParams.Owner = Enemy;
			QueryParams.SetAllowPartialPaths(false);

			// If there is a valid path from start to end.
			if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
			{
				
				UE_LOG(LogTemp, Warning, TEXT("VALID"));

				// Set enemy's memory location to the lookpoint created.
				Memory->SetActorLocation(LookPoint);

				// Set advance to true.
				bAdvance = true;
			}
			// If there is no valid path.
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("INVALID"));

				// Add one to the counter.
				Count++;
			}
		}
	}
	
	// Sets the memory location to the Lookpoint for the enemy to move to.
	

	// Set the memory location blackboard data for enemy.
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(TEXT("Memory"), Memory);

	return EBTNodeResult::Succeeded;
}