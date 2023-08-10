// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "SpawnPoint.h"


ASpawnPoint::ASpawnPoint()
{
	// Create box collider and attach to root.
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->AttachTo(RootComponent);

	// Attach ActorOverlap functionality to custom function
	OnActorBeginOverlap.AddDynamic(this, &ASpawnPoint::OnPlayerOverlap);

	bCanSpawn = true;
}

void ASpawnPoint::OnPlayerOverlap(AActor* Actor)
{
	// Get reference to player.
	AEric* Player = Cast<AEric>(Actor);

	// If player can spawn here, set players current spawn point to this, spawn enemies, and perform spawn check.
	if (bCanSpawn)
	{
		if (Player)
		{
			Player->CurrentSpawnPoint = this;

			SpawnEnemies();

			SpawnCheck();

			bCanSpawn = false;
		}	
	}
}

void ASpawnPoint::SpawnEnemies()
{
	// Go through all enemy spawn points and perform function SpawnEnemy.
	for (auto Iter(EnemySpawnPoints.CreateIterator()); Iter; Iter++)
	{
		if (*Iter)
		{
			(*Iter)->SpawnEnemy();
		}
	}
}

void ASpawnPoint::SpawnCheck()
{
	// If there are doors and they are open, close them and reset.
	if (Doors.Num() > 0)
	{
		for (auto Iter(Doors.CreateIterator()); Iter; Iter++)
		{
			if (*Iter)
			{
				if ((*Iter)->bIsOpened)
				{
					(*Iter)->AnimationTimeline.Reverse();

					(*Iter)->bIsOpened = false;

					UE_LOG(LogTemp, Warning, TEXT("DoorClosing"));
				}
			}
		}
	}
	// If there are vents and they are open, Move them back to start location and rotation and reset.
	if (Vents.Num() > 0)
	{
		for (auto Iter(Vents.CreateIterator()); Iter; Iter++)
		{
			if (*Iter)
			{
				if ((*Iter)->bIsOpened)
				{

					(*Iter)->SetActorLocation((*Iter)->VentStartLoc);

					(*Iter)->SetActorRotation((*Iter)->VentStartRot);

					(*Iter)->SetActorEnableCollision(true);

					(*Iter)->bIsOpened = false;

					UE_LOG(LogTemp, Warning, TEXT("DoorClosing"));
				}
			}
		}
	}
}
