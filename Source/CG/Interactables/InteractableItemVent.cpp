// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "InteractableItemVent.h"



AInteractableItemVent::AInteractableItemVent()
{
	// Allows the tick function to work.
	PrimaryActorTick.bCanEverTick = true;

	// Vent is not opened.
	bIsOpened = false;
}

void AInteractableItemVent::BeginPlay()
{
	Super::BeginPlay();

	// Binds created function to the animation timeline functionality.
	AnimationProgressDelegate.BindDynamic(this, &AInteractableItemVent::AnimationProgress);
	AnimationFinishDelegate.BindDynamic(this, &AInteractableItemVent::AnimationFinished);

	// Sets length of timeline.
	AnimationTimeline.SetTimelineLength(1.0f);

	// Tells which function to play when animation is finished.
	AnimationTimeline.SetTimelineFinishedFunc(AnimationFinishDelegate);

	// Adds a vector interpolation to the timeline.
	AnimationTimeline.AddInterpVector(AnimationCurve, AnimationProgressDelegate, TEXT("VentOffset"));

	// Get initial location and rotation of vent.
	VentStartLoc = GetActorLocation();

	VentStartRot = GetActorRotation();

}

void AInteractableItemVent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Updates the time in the animation timeline.
	AnimationTimeline.TickTimeline(DeltaTime);

}

bool AInteractableItemVent::Interact(AEric* InteractingCharacter)
{
	//Check for required items (screwdriver).
	if (AnimationCurve && InteractingCharacter->Inventory->Contains(SCREWDRIVER))
	{
		// if the vent is not open, perform animation. If not, Vent can not animate.
		if (!bIsOpened)
		{
			Animate();

			bIsOpened = true;

			SetActorEnableCollision(false);

			return true;	
		}
		else
		{
			return false;
		}
	}
	else
	{
		// Player does not have required item, play sound cue.
		InteractableAudioComponent->SetSound(VentLockSound);
		InteractableAudioComponent->Play();

		return false;
	}	
}

void AInteractableItemVent::Animate()
{
	// Plays animation and sound.
	AnimationTimeline.PlayFromStart();

}

void AInteractableItemVent::AnimationProgress(FVector Value)
{
	// Moves the vent based on the animation timeline and curve.
	//FVector move = FVector(1.0f * Value.X, 1.0f * Value.Y, 0.0f * Value.Z);

	//AddActorLocalOffset(move);

	FRotator rotate = FRotator(90.0f * Value.X, 1.0f * Value.Y, 0.0f * Value.Z);

	SetActorRotation(rotate);
}

void AInteractableItemVent::AnimationFinished()
{
	InteractableAudioComponent->SetSound(InteractSound);
	InteractableAudioComponent->Play();
}
