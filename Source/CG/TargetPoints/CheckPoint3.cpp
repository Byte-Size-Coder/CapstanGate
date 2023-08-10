// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "CheckPoint3.h"



void ACheckPoint3::BeginPlay()
{
	// Set start location and rotation of weapon item.
	if (Weapon)
	{
		WeaponLocation = Weapon->GetActorLocation();
		WeaponRotation = Weapon->GetActorRotation();
	}
}


void ACheckPoint3::SpawnCheck()
{
	Super::SpawnCheck();

	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	if (Player)
	{
		// If player standing, crouch him (spawning in vent).
		if (!Player->bIsCrouching)
		{
			Player->ToggleCrouch();
		}
		// If player has picked up the knife, remove it from player and reset it into game world.
		if (Player->bHasKnife)
		{
			Player->RemoveWeapon();

			AInteractableItemWeapon* Knife = GetWorld()->SpawnActor<AInteractableItemWeapon>(WeaponClass, WeaponLocation, WeaponRotation);

			Player->bHasKnife = false;
		}

	}
}
