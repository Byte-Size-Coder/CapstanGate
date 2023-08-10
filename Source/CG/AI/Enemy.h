// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "TargetPoints/Waypoint.h"
#include "TargetPoints/MemoryLocation.h"
#include "AI/EnemyController.h"
#include "Player/Eric.h"
#include "Enemy.generated.h"

UCLASS()
class CG_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties.
	AEnemy();

	// Tick function (update).
	virtual void Tick(float DeltaTime);

	/** Arrow Component for player's takedown position **/
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* TakedownPosition;

	/** Reference to Particle played at death **/
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* DeathParticle;

	/** Reference to the first waypoint Enemy will patrol to */
	UPROPERTY(EditInstanceOnly)
	AWaypoint* FirstWaypoint;

	/** Reference to enemy's spawn point **/
	UPROPERTY(EditInstanceOnly)
	class AWaypointSpawn* SpawnPoint;

	/** Bool variable to check to see if enemy is engaging the player **/
	UPROPERTY(BlueprintReadWrite)
	bool bEngaged;

	/** Enemy's memory location **/
	AMemoryLocation* PlayerMemory;

	// Bool variable to check if enemy sees the player.
	bool bSeesPlayer;

	
public:
// Public Functions

	// Function to set the enemy's memory location.
	void SetMemoryLocation(FVector Location);

	// Function to move enemy smoothly when attacking.
	void StartAttack(FVector StartLoc, FVector EndLoc, float Duration);

	// Function to turn enemy to face a certain way.
	void StartTurn(FRotator TargetRotation, float Duration);

	// Function to reset the enemy's stats
	void ResetEnemy();

	// Function to kill the player.
	void KillPlayer();

	/** Getters and Setter functions **/
	int32 GetPatrolPattern();

	float GetPatrolSpeed();

	float GetEngagedSpeed();

	float GetWanderSpeed();

	bool CanSeePlayer();

	bool HasSeenPlayer();

	bool IsAlert();

	bool HasKilledPlayer();

	void SetPatrolPattern(int32 Patrol);

	void SetSawPlayer(bool Saw);

	void SetKilledPlayer(bool Kill);

	UPROPERTY(EditDefaultsOnly, Category = EnemyStats)
	bool bEndEnemy;

private:
// Components and References

	/** First PawnSensing Component for Enemy */
	UPROPERTY(EditAnywhere)
		UPawnSensingComponent* PawnSensingComponent;

	/** Second PawnSensing Component for Enemy */
	UPROPERTY(EditAnywhere)
		UPawnSensingComponent* PawnSensingComponent2;

	/** Reference to Memory location**/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMemoryLocation> MemoryClass;

private:
// Editable Variables
	
	/** Base Walk speed for player*/
	UPROPERTY(EditInstanceOnly, Category = EnemyStats)
	int32 PatrolPattern;

	/** Base Walk speed for player*/
	UPROPERTY(EditDefaultsOnly, Category = EnemyStats)
	float PatrolSpeed;

	/** Sprinting speed for player*/
	UPROPERTY(EditDefaultsOnly, Category = EnemyStats)
	float EngagedSpeed;

	/** Sprinting speed for player*/
	UPROPERTY(EditDefaultsOnly, Category = EnemyStats)
	float WanderSpeed;

	/** Sprinting speed for player*/
	UPROPERTY(EditDefaultsOnly, Category = EnemyStats)
	float TurnSpeed;


private:
// Protected Functions

	// Function for when enemy sees player (with pawnsensing component).
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

private:
//Private Variables

	// Vector variables for start and end position for the StartAttack and StartTurn functions.
	FVector StartPosition;
	FVector EndPosition;

	// Rotator variables for start and end rotations for the StartAttack and StartTurn functions.
	FRotator StartRotation;
	FRotator EndRotation;

	// Float variables for the start and end times for the StartAttack and StartTurn functions.
	float StartTime;
	float EndTime;

	// Bool variable to check if enemy is attacking.
	bool bIsAttacking;

	// Bool variable to check if enemy is turning.
	bool bIsTurning;

	// Bool varianble to check if enemy is alert.
	bool bAlert;

	// Reference to the player.
	AEric* Player;

	// Bool variable to check if enemy killed the player.
	bool bKilledPlayer;

	// Bool variable to check if enemy saw the player.
	bool bSawPlayer;

};
