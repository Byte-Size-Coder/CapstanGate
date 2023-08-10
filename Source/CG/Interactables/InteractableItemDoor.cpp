// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "InteractableItemDoor.h"

AInteractableItemDoor::AInteractableItemDoor()
{
	// Allows the tick function to work.
	PrimaryActorTick.bCanEverTick = true;

	// Door is not open.
	bIsOpened = false;
	// Door can be open.
	bCanOpen = true;	

	bFinalDoor = false;
}

void AInteractableItemDoor::BeginPlay()
{
	Super::BeginPlay();

	// Binds created functions to the animation timeline functionality.
	AnimationProgressDelegate.BindDynamic(this, &AInteractableItemDoor::AnimationProgress);
	AnimationFinishDelegate.BindDynamic(this, &AInteractableItemDoor::AnimationFinished);

	// Sets length of timeline.
	AnimationTimeline.SetTimelineLength(1.f);

	// Tells which function to play when animation is finished.
	AnimationTimeline.SetTimelineFinishedFunc(AnimationFinishDelegate);

	// Adds a vector interpolation to the timeline.
	AnimationTimeline.AddInterpVector(AnimationCurve, AnimationProgressDelegate, TEXT("DoorOffset"));
}

void AInteractableItemDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Updates the time in the animation timeline.
	AnimationTimeline.TickTimeline(DeltaTime);

}

bool AInteractableItemDoor::Interact(class AEric* InteractingCharacter)
{
	// If Door is one that player is not suppose to go through, play certain voice cue.
	if (bIsLockedCantOpen || bFinalDoor)
	{
		InteractableAudioComponent->SetSound(DoorLockSound);
		InteractableAudioComponent->Play();

		return false;
	}

	// If door is lock with certain keycard requirements and player has them, follow opening procedures.
	if (bIsLockedCardA && InteractingCharacter->Inventory->Contains(KEYCARD_A))
	{
		if (bCanOpen && AnimationCurve)
		{
			// change the variable of the door being open or closed
			if (bIsOpened)
			{
				bIsOpened = false;
			}
			else
			{
				bIsOpened = true;
			}

			Animate();
			return true;
		}
	}
	else if (bIsLockedCardB && InteractingCharacter->Inventory->Contains(KEYCARD_B))
	{
		if (bCanOpen && AnimationCurve)
		{
			// change the variable of the door being open or closed
			if (bIsOpened)
			{
				bIsOpened = false;
			}
			else
			{
				bIsOpened = true;
			}

			Animate();
			return true;
		}
	}
	// If it is a regular door the player can open, follow opening procedures.
	else if (!bIsLockedCardA && !bIsLockedCardB)
	// If you can open the door, and there is a reference to the animation curve, open the door.
	{
		if (bCanOpen && AnimationCurve)
		{
			// change the variable of the door being open or closed
			if (bIsOpened)
			{
				bIsOpened = false;
			}
			else
			{
				bIsOpened = true;
			}

			Animate();
			return true;
		}
		else
		{
			return false;
		}
	}
	// All else statements fail, can not open door, play certain sound cues.
	InteractableAudioComponent->SetSound(DoorLockSound);
	InteractableAudioComponent->Play();
	return false;
}

void AInteractableItemDoor::Animate()
{
	//Sets so you can not open or close the door while the animation is playing (stops spamming).
	bCanOpen = false;

	// Plays the correct animation and sounds if you are opening or closing the door.
	if (!bIsOpened || bFinalDoor)
	{
		AnimationTimeline.Reverse();

		InteractableAudioComponent->SetSound(DoorCloseSound);
		InteractableAudioComponent->Play();

		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		AnimationTimeline.PlayFromStart();
		if (bIsLockedCardA || bIsLockedCardB || bIsLockedCardC)
		{
			InteractableAudioComponent->SetSound(DoorOpenWithCardSound);
			InteractableAudioComponent->Play();
		}
		else
		{
			InteractableAudioComponent->SetSound(InteractSound);
			InteractableAudioComponent->Play();
		}
		
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AInteractableItemDoor::AnimationProgress(FVector Value)
{
	// Rotates the door based on the animation timeline and curve.
	FRotator rotate = FRotator(0.0f * Value.X, 90.0f * Value.Y, 0.0f * Value.Z);

	SetActorRotation(rotate);
}


void AInteractableItemDoor::AnimationFinished()
{
	// Can open or close the door after the animation is finished.
	bCanOpen = true;

	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

