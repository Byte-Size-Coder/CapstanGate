// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactables/InteractableItem.h"
#include "Weapons/Weapon.h"
#include "InteractableItemWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AInteractableItemWeapon : public AInteractableItem
{
	GENERATED_BODY()
	
public:

	// Function that interacts with the item.
	virtual bool Interact(class AEric* InteractingCharacter) override;

	// Function that gets the reference to the weapon.
	TSubclassOf<AWeapon> GetWeaponClass() { return WeaponClass; }

protected:
//References and Editables
	/**Reference to the weapon to spawn into player's hand */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

private:
//Functions

	// Function to pick up the item.
	void PickUp();

private:
//Variables

	// Timer handle for picking up item.
	FTimerHandle PickUpTime;

};
