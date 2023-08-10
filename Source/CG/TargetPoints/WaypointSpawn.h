// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TargetPoints/Waypoint.h"
#include "WaypointSpawn.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AWaypointSpawn : public AWaypoint
{
	GENERATED_BODY()

public:

	AWaypointSpawn();

	// Refrence to the spawn position.
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* ResetPosition;

	// Bool variable to check enemy is spawned.
	UPROPERTY(EditInstanceOnly)
	bool bIsSpawned;

	// Function to spawn enemy.
	void SpawnEnemy();

protected:

	/**Reference to enemy to spawn */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemy> EnemyClass;

	// Int variable to indicate what patrol pattern to follow.
	UPROPERTY(EditInstanceOnly)
	int32 EnemyPatrolPattern;

	// Reference to the spawned enemy.
	class AEnemy* EnemyRef;
	
};
