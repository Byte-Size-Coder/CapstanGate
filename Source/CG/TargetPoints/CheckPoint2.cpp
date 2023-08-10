// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "CheckPoint2.h"

void ACheckPoint2::BeginPlay()
{
	// Set start location and rotation of both utlity items.
	if (UtilityItem1)
	{
		Utility1Location = UtilityItem1->GetActorLocation();
		Utility1Rotation = UtilityItem1->GetActorRotation();
	}
	if (UtilityItem2)
	{
		Utility2Location = UtilityItem2->GetActorLocation();
		Utility2Rotation = UtilityItem2->GetActorRotation();
	}
}


void ACheckPoint2::SpawnCheck()
{
	// Call base class function
	Super::SpawnCheck();

	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// If player has picked up either utility items, remove the specific item(s) and reset it (them) to the game world.
	if (Player)
	{

		if (Player->Inventory->Contains(UtilityType1))
		{
			Player->Inventory->Remove(UtilityType1);

			AInteractableItemUtility* KeyCard = GetWorld()->SpawnActor<AInteractableItemUtility>(UtilityClass1, Utility1Location, Utility1Rotation);
		}

		if (Player->Inventory->Contains(UtilityType2))
		{
			Player->Inventory->Remove(UtilityType2);

			AInteractableItemUtility* KeyCard = GetWorld()->SpawnActor<AInteractableItemUtility>(UtilityClass2, Utility2Location, Utility2Rotation);
		}
	}
}
