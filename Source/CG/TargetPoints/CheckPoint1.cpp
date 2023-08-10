// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "CheckPoint1.h"


void ACheckPoint1::BeginPlay()
{
	// Get start location and rotation of utility item.
	if (UtilityItem)
	{
		UtilityLocation = UtilityItem->GetActorLocation();
		UtilityRotation = UtilityItem->GetActorRotation();
	}
}

void ACheckPoint1::SpawnCheck()
{
	// Call base class function
	Super::SpawnCheck();

	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// If player has picked up that utility item, remove it from inventory and reset it in the world.
	if (Player)
	{
		if (Player->Inventory->Contains(UtilityType))
		{
			Player->Inventory->Remove(UtilityType);

			AInteractableItemUtility* KeyCard = GetWorld()->SpawnActor<AInteractableItemUtility>(UtilityClass, UtilityLocation, UtilityRotation);
		}
	}
}