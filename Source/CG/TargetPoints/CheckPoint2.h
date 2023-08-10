// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TargetPoints/SpawnPoint.h"
#include "Interactables/InteractableItemUtility.h"
#include "Interactables/InteractableItemDoor.h"
#include "CheckPoint2.generated.h"

/**
 * 
 */



UCLASS()
class CG_API ACheckPoint2 : public ASpawnPoint
{
	GENERATED_BODY()
	
public:

	void BeginPlay();

	virtual void SpawnCheck() override;

	/** Reference to the class of first utility item **/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractableItemUtility> UtilityClass1;

	/** Reference to the class of second utility item **/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractableItemUtility> UtilityClass2;

	/** Reference to first utlity item **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	AInteractableItemUtility* UtilityItem1;

	/** Reference to second utlity item **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	AInteractableItemUtility* UtilityItem2;

	/** Reference to first utlity item type **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	TEnumAsByte<EInteractableUtilityType> UtilityType1;

	/** Reference to second utlity item type **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	TEnumAsByte<EInteractableUtilityType> UtilityType2;

	// References to start location and rotation of both utlity items.
	FVector Utility1Location;

	FRotator Utility1Rotation;

	FVector Utility2Location;

	FRotator Utility2Rotation;

};
