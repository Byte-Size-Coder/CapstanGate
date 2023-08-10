// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "InteractableItemWeapon.h"


bool AInteractableItemWeapon::Interact(AEric* InteractingCharacter)
{
	Super::Interact(InteractingCharacter);

	InteractingCharacter->DisablePlayerInput();
	// Switch variable to indicate player is picking up item to play correct animation.
	InteractingCharacter->bPickUpKnife = true;
	
	// Set a timer so the item is picked up and disappears from the world at the correct time of animation.
	GetWorld()->GetTimerManager().SetTimer(PickUpTime, this, &AInteractableItemWeapon::PickUp, 1.0f, false);

	// Play specific interaction sounds.
	InteractableAudioComponent->SetSound(InteractSound);

	return true;
}


void AInteractableItemWeapon::PickUp()
{
	// Get refrence to player to eqiup weapon to.
	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		Player->EquipWeapon(this);

		// Destroys the weapon from the world.
		Destroy();
	}	
}

