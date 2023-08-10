// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DistractionTV.generated.h"

UCLASS()
class CG_API ADistractionTV : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ADistractionTV();

	//** Component to hold a location**/
	UPROPERTY(EditAnywhere)
	USceneComponent* Spot;

	// function when TV is interacted.
	void Interact();

protected:
// Components

	/** Static Mesh for Item */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Sounds)
	UAudioComponent * AudioComponent;

protected:
// References and editables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * TVOnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * TVOffSound;

	/** Reference to the on and off materials of the tv **/
	UPROPERTY(EditAnywhere)
		UMaterial * OnMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial * OffMaterial;

	// Float variable for the distance the tv attracts enemies.
	UPROPERTY(EditAnywhere)
	float TvToEnemyDist;

private:
// Functions

	// Function to turn off the tv.
	void TurnOff();

private:
// Variables

	// Timer to handle the on time of the tv.
	FTimerHandle OnTime;

	// Bool varialbe to check if tv is on.
	bool bIsOn;

};
