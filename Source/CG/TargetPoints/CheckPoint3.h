// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TargetPoints/SpawnPoint.h"
#include "Interactables/InteractableItemWeapon.h"
#include "Interactables/InteractableItemUtility.h"
#include "Interactables/InteractableItemDoor.h"
#include "CheckPoint3.generated.h"

/**
 * 
 */
UCLASS()
class CG_API ACheckPoint3 : public ASpawnPoint
{
	GENERATED_BODY()
	
public:

	void BeginPlay();

	virtual void SpawnCheck() override;

	/** Reference to weapon class **/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractableItemWeapon> WeaponClass;

	/** Reference to weapon item **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	AInteractableItemWeapon* Weapon;

	// Reference to start location and rotation of weapon item.
	FVector WeaponLocation;
	
	FRotator WeaponRotation;

};
