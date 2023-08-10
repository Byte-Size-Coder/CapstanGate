// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "InteractableItemUtility.h"


bool AInteractableItemUtility::Interact(AEric* InteractingCharacter)
{
	// Call base class function.
	Super::Interact(InteractingCharacter);

	// Switch variable to indicate player is picking up item to play correct animation.
	InteractingCharacter->bPickUp = true;

	// Set a timer so the item is picked up and disappears from the world at the correct time of animation.
	GetWorld()->GetTimerManager().SetTimer(PickUpTime, this, &AInteractableItemUtility::PickUp, 0.75f, false);

	// Play specific interaction sounds.
	InteractableAudioComponent->SetSound(InteractSound);
	InteractableAudioComponent->Play();

	return true;
}


void AInteractableItemUtility::PickUp()
{
	// Get refrence to player and their inventory to add item to.
	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		Player->Inventory->PickUp(this);
	}
}
