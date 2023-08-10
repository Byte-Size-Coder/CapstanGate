// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

UCLASS()
class CG_API AInteractableItem : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties.
	AInteractableItem();

	// Function that indicates player can interact.
	virtual bool Interact(class AEric* InteractingCharacter);

protected:
// Componentes

	/** Sphere collider that triggers interact */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collider;

	/** Static Mesh for Item */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	/** Audio Component for interaction**/
	UPROPERTY(VisibleAnywhere, Category = Sounds)
	UAudioComponent * InteractableAudioComponent;


protected:
// Refrences and Editables

	/** Sounds **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * InteractSound;


protected:
//Functions

	// Function for player overlap.
	UFUNCTION()
	void OnPlayerOverlap(AActor* InteractingPlayer);

	// Function for player ends overlap.
	UFUNCTION()
	void OnPlayerEndOverlap(AActor* InteractingPlayer);

};
