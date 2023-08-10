// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Interactables/InteractableItemUtility.h"
#include "Inventory.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CG_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();
	
	// Function to pick up items.
	void PickUp(AInteractableItemUtility* Item);

	void Remove(EInteractableUtilityType Type);

	// Function to check if player has item.
	bool Contains(EInteractableUtilityType Type);

private:
	
	// Array list of items.
	TArray<EInteractableUtilityType> Inventory;

};
