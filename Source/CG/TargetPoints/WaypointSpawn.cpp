// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "WaypointSpawn.h"



AWaypointSpawn::AWaypointSpawn()
{
	// Create arrow component and attach to root.
	ResetPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("TakedownPosition"));
	ResetPosition->AttachTo(RootComponent);
}


void AWaypointSpawn::SpawnEnemy()
{
	// If enemy is not spawned.
	if (!bIsSpawned)
	{
		// Spawned in enemy.
		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, ResetPosition->GetComponentLocation(), ResetPosition->GetComponentRotation());

		// Set necessary variables and reference to spawned enemy.
		SpawnedEnemy->SpawnPoint = this; 

		SpawnedEnemy->SetPatrolPattern(EnemyPatrolPattern);

		SpawnedEnemy->FirstWaypoint = NextWaypoint;

		SpawnedEnemy->SpawnDefaultController();

		// Set reference.
		EnemyRef = SpawnedEnemy;

		// Set variable to indicate enemy is spawned.
		bIsSpawned = true;
	}
	// If enemy is spawned.
	else
	{
		// Reset enemy's position and stats (variables and blackboard data)
		if (EnemyRef)
		{
			AEnemyController* EnemyRefC = Cast<AEnemyController>(EnemyRef->GetController());

			EnemyRef->SetActorLocation(ResetPosition->GetComponentLocation());

			EnemyRef->SetActorRotation(ResetPosition->GetComponentRotation());
			
			EnemyRefC->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Waypoint"), NextWaypoint);

			EnemyRef->ResetEnemy();
		}
	}
}
