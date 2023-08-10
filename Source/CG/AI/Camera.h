// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Perception/PawnSensingComponent.h"
#include "Player/Eric.h"
#include "Camera.generated.h"

////////////////////////Prototype - Not used In Game ///////////////////////////////////////////////////////////

UCLASS()
class CG_API ACamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACamera();

	void BeginPlay();

	void Tick(float DeltaTime);

	/** Reference to the animation curve */
	UPROPERTY(EditAnywhere)
	UCurveVector* AnimationCurve;


protected:

	// Animation timeline for curve.
	FTimeline AnimationTimeline;

	// Animation progress for curve.
	FOnTimelineVector AnimationProgressDelegate;

	// Animation finished for curve.
	FOnTimelineEvent AnimationFinishDelegate;

	FTimerHandle WaitTime;

	// Function for the progression of the animation.
	UFUNCTION()
	void AnimationProgress(FVector Value);

	// Function for when the animation is finished.
	UFUNCTION()
	void AnimationFinished();

	void Animate();

	/** PawnSensing Component for Camera */
	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* PawnSensingComponent;

	/** Static Mesh for Item */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Function for when Camera sees player (with pawnsensing component).
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	bool bMovingLeft;

	bool bSeesPlayer;

	AEric* Player;
	
};
