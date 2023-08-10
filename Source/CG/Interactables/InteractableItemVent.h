// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactables/InteractableItem.h"
#include "InteractableItemVent.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AInteractableItemVent : public AInteractableItem
{
	GENERATED_BODY()
	
public:

	AInteractableItemVent();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Function that interacts with vent.
	virtual bool Interact(AEric* InteractingCharacter) override;

	// Reference to the starting location of the vent.
	FVector VentStartLoc;

	// Reference to the starting Rotation of the vent.
	FRotator VentStartRot;

	// Variable to check if it is open.
	bool bIsOpened;

	// Function to animate the vent.
	void Animate();

	// Animation timeline for curve.
	FTimeline AnimationTimeline;

protected:
//References and Editables
	/** Reference to the animation curve */
	UPROPERTY(EditAnywhere)
	UCurveVector* AnimationCurve;

	/** Reference to Audio Clip **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * VentLockSound;

protected:
//functions
	
	// Function for the progression of the animation.
	UFUNCTION()
		void AnimationProgress(FVector Value);

	// Function for when the animation is finished.
	UFUNCTION()
		void AnimationFinished();

private:

	// Animation progress for curve.
	FOnTimelineVector AnimationProgressDelegate;

	// Animation finished for curve.
	FOnTimelineEvent AnimationFinishDelegate;
	
};
