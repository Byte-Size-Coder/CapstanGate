// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactables/InteractableItem.h"
#include "InteractableItemUtility.generated.h"

UENUM()
enum EInteractableUtilityType
{
	KEYCARD_A,
	KEYCARD_B,
	SCREWDRIVER,
	REMOTE
};

UCLASS()
class CG_API AInteractableItemUtility : public AInteractableItem
{
	GENERATED_BODY()
		
public:

	/**Reference to the type of utility item (Enum)**/
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EInteractableUtilityType> Type;
	
	// Function that interacts with the item.
	virtual bool Interact(class AEric* InteractingCharacter) override;

private:
//Functions

	// Function to pick up the item.
	void PickUp();

private:
//Variables

	// Timer handle for picking up item.
	FTimerHandle PickUpTime;

};
