// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "UI/EricHUD.h"
#include "InteractableItem.h"


// Sets default values
AInteractableItem::AInteractableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creates a root component for the actor.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Creates a collider and attaches it to root component.
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->AttachTo(RootComponent);

	// Creates a mesh and attaches it to root component.
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	// Create audio component and attach it to root component.
	InteractableAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	InteractableAudioComponent->AttachTo(RootComponent);

	// Attached ActorOveralp functionality to custom functions.
	OnActorBeginOverlap.AddDynamic(this, &AInteractableItem::OnPlayerOverlap);
	OnActorEndOverlap.AddDynamic(this, &AInteractableItem::OnPlayerEndOverlap);

}

bool AInteractableItem::Interact(AEric* InteractingCharacter)
{
	// base function for this class, it is called when player is in range to interact.
	return true;
}

void AInteractableItem::OnPlayerOverlap(AActor* InteractingPlayer)
{
	// Get reference to player.
	AEric* Player = Cast<AEric>(InteractingPlayer);

	// If player exists, show the interact text on HUD
	if (Player)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (HUD)
		{
			HUD->ShowInteractText();
		}
	}
}

void AInteractableItem::OnPlayerEndOverlap(AActor* InteractingPlayer)
{
	// Get reference to player.
	AEric* Player = Cast<AEric>(InteractingPlayer);

	// If player exists, remove the interact text on HUD
	if (Player)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (HUD)
		{
			HUD->HideInteractText();
		}
	}
}





