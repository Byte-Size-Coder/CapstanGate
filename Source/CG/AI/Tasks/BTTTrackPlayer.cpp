// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BTTTrackPlayer.h"


UBTTTrackPlayer::UBTTTrackPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTTrackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
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

	// Create a vector trackpoint.
	FVector TrackPoint = FVector::ZeroVector;

	// Create bool variable to check if tracking the enemy first time fails.
	bool bTrackFailed = false;


	// If the enemy saw the player at all, and the player's distance is less then 500, set the track point close the player
	if (Enemy->HasSeenPlayer() && Dist <= 500.0f)
	{
		// Create necessary variables for loop.
		bool bAdvance = false;

		int Count = 0;

		// Continue loop if advance remains false or the counter is less then 10.
		while (!bAdvance && Count <= 10)
		{
			// Create a vector (LookPoint) and set its locations to a random location close around the player.
			TrackPoint.X = PlayerLocation.X + FMath::FRandRange(-100, 100);
			TrackPoint.Y = PlayerLocation.Y + FMath::FRandRange(-100, 100);
			TrackPoint.Z = PlayerLocation.Z;

			if (Nav)
			{
				// Create a path findy query and set its parameters.
				FPathFindingQuery QueryParams;
				QueryParams.StartLocation = EnemyLocation;
				QueryParams.EndLocation = TrackPoint;
				QueryParams.NavData = Nav->GetMainNavData();
				QueryParams.Owner = Enemy;
				QueryParams.SetAllowPartialPaths(false);

				// If there is a valid path from start to end.
				if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
				{
					UE_LOG(LogTemp, Warning, TEXT("VALID TRACK OF PLAYER CLOSE"));

					// Set enemy's memory location to the lookpoint created.
					Memory->SetActorLocation(TrackPoint);

					// Set advance to true.
					bAdvance = true;

					// Set enemy saw the player to false.
					Enemy->SetSawPlayer(false);
				}
				// If there is no valid path.
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("INVALID TRACK OF PLAYER CLOSE"));

					// Add 1 to the counter
					Count++;
				}
			}
		}

		// If advance is still false after counter goes beyond 10, The player track failed.
		if (!bAdvance)
		{
			bTrackFailed = true;
		}
	}
	// If the enemy saw the player at all, and the player's distance is less then 1500, set the track point near the player
	else if (Enemy->HasSeenPlayer() && Dist <= 1500.0f)
	{
		// Create necessary variables for loop.
		bool bAdvance = false;

		int Count = 0;

		// Continue loop if advance remains false or the counter is less then 10.
		while (!bAdvance && Count <= 10)
		{
			// Create a vector (LookPoint) and set its locations to a random location near the player.
			TrackPoint.X = PlayerLocation.X + FMath::FRandRange(-500, 500);
			TrackPoint.Y = PlayerLocation.Y + FMath::FRandRange(-500, 500);
			TrackPoint.Z = PlayerLocation.Z;

			if (Nav)
			{
				// Create a path findy query and set its parameters.
				FPathFindingQuery QueryParams;
				QueryParams.StartLocation = EnemyLocation;
				QueryParams.EndLocation = TrackPoint;
				QueryParams.NavData = Nav->GetMainNavData();
				QueryParams.Owner = Enemy;
				QueryParams.SetAllowPartialPaths(false);

				// If there is a valid path from start to end.
				if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
				{
					UE_LOG(LogTemp, Warning, TEXT("VALID TRACK OF PLAYER FAR"));

					// Set enemy's memory location to the lookpoint created.
					Memory->SetActorLocation(TrackPoint);

					// Set advance to true.
					bAdvance = true;

					// Set enemy saw the player to false.
					Enemy->SetSawPlayer(false);
				}
				// If there is no valid path.
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("INVALID TRACK OF PLAYER FAR"));

					// Add 1 to counter.
					Count++;
				}
			}
		}

		// If advance is still false after counter goes beyond 10, The player track failed.
		if (!bAdvance)
		{
			bTrackFailed = true;
		}
	}
	// IF player's distance to enemy is father then 1500, then player track has failed aswell.
	else
	{
		bTrackFailed = true;
	}

	// If player Track has failed.
	if (bTrackFailed)
	{
		// Create necessary variables for loop.
		bool bAdvance = false;

		bool bTrackFailedAgain = false;

		int Count = 0;

		// Continue loop if advance remains false or the counter is less then 10.
		while (!bAdvance && Count <= 10)
		{

			// Create a vector (LookPoint) and set its locations to a random location around the enemy's memory location.
			TrackPoint.X = MemoryLocation.X + FMath::FRandRange(-300, 300);
			TrackPoint.Y = MemoryLocation.Y + FMath::FRandRange(-300, 300);
			TrackPoint.Z = MemoryLocation.Z;

			if (Nav)
			{
				// Create a path findy query and set its parameters.
				FPathFindingQuery QueryParams;
				QueryParams.StartLocation = EnemyLocation;
				QueryParams.EndLocation = TrackPoint;
				QueryParams.NavData = Nav->GetMainNavData();
				QueryParams.Owner = Enemy;
				QueryParams.SetAllowPartialPaths(false);

				// If there is a valid path from start to end.
				if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
				{
					UE_LOG(LogTemp, Warning, TEXT("VALID TRACKFAILED"));

					// Set enemy's memory location to the lookpoint created.
					Memory->SetActorLocation(TrackPoint);

					// Set advance to true.
					bAdvance = true;

					// Set enemy saw the player to false.
					Enemy->SetSawPlayer(false);
				}
				// If there is no valid path.
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("INVALID TRACKFAILED"));

					// Add 1 to counter.
					Count++;
				}
			}
		}
		// If advance is STILL false after counter is over 10, normal track failed aswell, move to final stage.
		if (!bAdvance)
		{
			bTrackFailedAgain = true;
		}

		// If all other tracks failed.
		if (bTrackFailedAgain)
		{
			// Create necessary variables for loop
			bool bAdvance = false;

			int Count = 0;

			// Continue loop if advance remains false or the counter is less then 10.
			while (!bAdvance && Count <= 10)
			{
				// Create a vector (LookPoint) and set its locations to a random location around the enemy's location.
				TrackPoint.X = EnemyLocation.X + FMath::FRandRange(-300, 300);
				TrackPoint.Y = EnemyLocation.Y + FMath::FRandRange(-300, 300);
				TrackPoint.Z = EnemyLocation.Z;

				if (Nav)
				{
					// Create a path findy query and set its parameters.
					FPathFindingQuery QueryParams;
					QueryParams.StartLocation = EnemyLocation;
					QueryParams.EndLocation = TrackPoint;
					QueryParams.NavData = Nav->GetMainNavData();
					QueryParams.Owner = Enemy;
					QueryParams.SetAllowPartialPaths(false);

					// If there is a valid path from start to end.
					if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
					{
						UE_LOG(LogTemp, Warning, TEXT("VALID TRACKFAILED FINAL"));

						// Set enemy's memory location to the lookpoint created.
						Memory->SetActorLocation(TrackPoint);

						// Set advance to true.
						bAdvance = true;

						// Set enemy saw the player to false.
						Enemy->SetSawPlayer(false);
					}
					// If there is no valid path.
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("INVALID TRACKFAILED FINAL"));

						// Add 1 to counter.
						Count++;
					}
				}
			}
		}
	}

	// Set the memory location blackboard data for enemy.
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(TEXT("Memory"), Memory);

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(TEXT("bScream"), true);

	return EBTNodeResult::Succeeded;
}

