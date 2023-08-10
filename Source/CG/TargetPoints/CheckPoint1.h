// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TargetPoints/SpawnPoint.h"
#include "Interactables/InteractableItemUtility.h"
#include "CheckPoint1.generated.h"

/**
 * 
 */
UCLASS()
class CG_API ACheckPoint1 : public ASpawnPoint
{
	GENERATED_BODY()
	
public:

	void BeginPlay();

	virtual void SpawnCheck() override;
	
	/** Reference to the utility class **/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractableItemUtility> UtilityClass;

	/** Reference to specific utility item **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	AInteractableItemUtility* UtilityItem;

	/** Reference to the utility item type **/
	UPROPERTY(EditInstanceOnly, Category = ItemReferences)
	TEnumAsByte<EInteractableUtilityType> UtilityType;

	//Reference to start location and rotation of the utility item.
	FVector UtilityLocation;

	FRotator UtilityRotation;

};