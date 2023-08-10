// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactables/InteractableItem.h"
#include "InteractableItemDoor.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AInteractableItemDoor : public AInteractableItem
{
	GENERATED_BODY()
	
	
public:
	AInteractableItemDoor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//Function that interacts with door.
	virtual bool Interact(class AEric* InteractingCharacter) override;

	// Variable for if the door is open.
	bool bIsOpened;

	// Function to animate the door.
	UFUNCTION(BlueprintCallable, Category = OpenAndClose)
	void Animate();

	// Animation timeline for curve.
	FTimeline AnimationTimeline;

protected:
// References and Editables

	/** Reference to the animation curve */
	UPROPERTY(EditAnywhere)
	UCurveVector* AnimationCurve;

	/** Bool variable to check if door is locked with KeyCardA access **/
	UPROPERTY(EditInstanceOnly)
	bool bIsLockedCantOpen;

	/** Bool variable to check if door is locked with KeyCardA access **/
	UPROPERTY(EditInstanceOnly)
	bool bIsLockedCardA;

	/** Bool variable to check if door is locked with KeyCardB access **/
	UPROPERTY(EditInstanceOnly)
	bool bIsLockedCardB;

	/** Bool variable to check if door is locked with KeyCardB access **/
	UPROPERTY(EditInstanceOnly)
	bool bIsLockedCardC;

	UPROPERTY(BlueprintReadWrite)
	bool bFinalDoor;

	/** Sounds **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * DoorCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * DoorOpenWithCardSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * DoorLockSound;

protected:
//Functions

	// Function for the progression of the animation.
	UFUNCTION()
	void AnimationProgress(FVector Value);

	// Function for when the animation is finished.
	UFUNCTION()
	void AnimationFinished();

private:
//Variables

	// Animation progress for curve.
	FOnTimelineVector AnimationProgressDelegate;

	// Animation finished for curve.
	FOnTimelineEvent AnimationFinishDelegate;

	// Variable for if you can open the door.
	bool bCanOpen;

};
