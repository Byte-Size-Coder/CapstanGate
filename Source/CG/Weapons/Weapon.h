// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CG_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon();

	// Function that gets the reference to the pickup weapon.
	TSubclassOf<class AInteractableItemWeapon> GetInteractableWeaponClass() { return InteractableWeaponClass; }

protected:

	/** Static Mesh for Weapon */
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	/** Reference to the pickup item blueprint of this weapon */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AInteractableItemWeapon> InteractableWeaponClass;	
};
