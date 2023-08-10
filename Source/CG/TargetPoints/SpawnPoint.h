// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "TargetPoints/WaypointSpawn.h"
#include "Interactables/InteractableItemDoor.h"
#include "Interactables/InteractableItemVent.h"
#include "SpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class CG_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	ASpawnPoint();

	// Function to spawn in enemies
	void SpawnEnemies();

	// Function to check to reset game.
	virtual void SpawnCheck();

	// Bool variable to check if player can spawn.
	bool bCanSpawn;

protected:

	/** Box Collider **/
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collider;

	/** Reference to the enemy spawn points **/
	UPROPERTY(EditInstanceOnly, Category = EnemySpawns)
	TArray<AWaypointSpawn*> EnemySpawnPoints;

	/** Reference to certain doors **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	TArray<AInteractableItemDoor*> Doors;

	/** Reference to certain vents **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	TArray<AInteractableItemVent*> Vents;

	// Function for when player overlap.
	UFUNCTION()
	void OnPlayerOverlap(AActor* Actor);

};
