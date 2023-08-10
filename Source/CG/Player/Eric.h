// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Player/Inventory.h"
#include "TargetPoints/SpawnPoint.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Eric.generated.h"

UCLASS()
class CG_API AEric : public ACharacter
{
	GENERATED_BODY()


public:
	/** Sets default values for this character's properties*/
	AEric();

	// Update function.
	virtual void Tick(float DeltaTime);

	// Inventory Component for player.
	UPROPERTY(VisibleAnywhere)
	UInventory* Inventory;

public:
//Blueprint Variables//

	// Bool variable to check when player picks up items.
	UPROPERTY(BlueprintReadWrite)
	bool bPickUp;

	// Bool variable to check when player picks up knife.
	UPROPERTY(BlueprintReadWrite)
	bool bPickUpKnife;

	// Bool variable to check when player attacks enemy.
	UPROPERTY(BlueprintReadWrite)
	bool bTakeDown;

	// Bool variable to check when player is crouched.
	UPROPERTY(BlueprintReadWrite)
	bool bIsCrouching;

	// Bool variable to check when player is in the vent.
	UPROPERTY(BlueprintReadWrite)
	bool bInVent;

	// Bool variable to check when player has the knife.
	UPROPERTY(BlueprintReadWrite)
	bool bHasKnife;

	// Bool variable to check what takedown move player makes.
	UPROPERTY(BlueprintReadWrite)
	int32 TakeDownMove;

	UPROPERTY(BlueprintReadWrite)
	bool bRemotetut;

	UPROPERTY(BlueprintReadWrite)
	bool bScrewdrivertut;

	UPROPERTY(BlueprintReadWrite)
	bool bKnifetut;

	//UPROPERTY(BlueprintReadWrite)
	//bool bKillVoices;

public:

//public functions//

	// Function to equip weapon to player.
	void EquipWeapon(class AInteractableItemWeapon* WeaponPickup);

	// Function to remove weapon from player.
	UFUNCTION(BlueprintCallable, Category = Knife)
	void RemoveWeapon();

	// Function to Show the Death Widget on player's death.
	void ShowDeathWidget();

	// Function to Move and rotate behind enemy upon attack.
	void StartAttack(FVector StartLoc, FVector EndLoc, float Duration);

	// Function to turn player smoothly.
	void StartTurn(FVector StartLoc, FVector EndLoc, float Duration);

	// Function to check if player is seen or alerted.
	void Seen();

	// Function for when enemy attacks players.
	void LookAndLock(class AEnemy* Target);

	// Function to spawn player
	void SpawnPlayer();

	// Function to kill the enemy.
	void KillEnemy();

	// Funtion that toggles player to crouch or uncrouch.
	void ToggleCrouch();

	// Function to toggle HUD
	void ToggleHUD();

	// Function to Show blood splatter on attack.
	void ShowBloodSplatterWidget();

	void DisablePlayerInput();

	UFUNCTION(BlueprintCallable, Category = Input)
	void EnablePlayerInput();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowRemoteTutorial();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowScrewDriverTutorial();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowKnifeTutorial();

public:

	// Public Variables

	// Reference to player spawn point.
	ASpawnPoint* CurrentSpawnPoint;

	// Bool variable to check when player is Seen.
	bool bIsSeen;

	// Bool variable to check when player is alerted.
	bool bAlerted;

	// Bool variable to check when player is being attacked.
	bool bAttacked;

	// Bool to check when Hud Button is down.
	bool bHUDButtonDown;

	// Float variable for player's stamina
	float Stamina;


protected:

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCamera;

	/** Camera Shakes **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	TSubclassOf<UCameraShake> RunCameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	TSubclassOf<UCameraShake> EndRunCameraShake;

	/** Sphere collider for takedowns*/
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Collider;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* MeshArms;

protected:	

	/** Audio Component Movements **/
	UPROPERTY(VisibleAnywhere, Category = Sounds)
	UAudioComponent * MovementAudioComponent;

	/** Audio Component Vocals **/
	UPROPERTY(VisibleAnywhere, Category = Sounds)
	UAudioComponent * VocalAudioComponent;

	/** SOUNDS **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * OutOfBreathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * EquipKnifeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * FirstKillVocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * ThirdKillVocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * FifthKillVocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * SeventhKillVocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * TenthKillVocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase * NoKillVocal;

protected:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Base Walk speed for player*/
	UPROPERTY(EditAnywhere, Category = PlayerStats)
	float WalkSpeed;

	/** Sprinting speed for player*/
	UPROPERTY(EditAnywhere, Category = PlayerStats)
	float SprintSpeed;

	/** Radius for Interaction spherecast*/
	UPROPERTY(EditAnywhere, Category = PlayerStats)
	float InteractionRadius;

	/** Base Walk speed for player*/
	UPROPERTY(EditAnywhere, Category = PlayerStats)
	float AttackSpeed;

	/** Base Walk speed for player*/
	UPROPERTY(EditAnywhere, Category = PlayerStats)
	float TurnSpeed;

	// Float variable for how far the remote can turn on the TV.
	UPROPERTY(EditAnywhere, Category = PlayerStats)
	float RemoteToTvDist;


private:

	// Called to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Handles moving forward/backward. */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right. */
	void MoveRight(float Val);

	/** Handles looking left and right. **/
	void TurnAtRate(float Rate);

	/** Handles looking Up and Down. **/
	void LookUpAtRate(float Rate);

	// Function to start the movement sound.
	void StartMoveSound();

	// Function to end the movement sound.
	void EndMoveSound();

	// Function for player to start sprinting.
	void StartSprint();

	// Function for Player to stop sprinting.
	void EndSprint();

private:

	// Function for when player interacts with interacting items.
	void OnInteract();

	// Function for when player uses the remote.
	void UseRemote();

	// Function to take down the enemy.
	void TakeDown();
	
	// Function to restore players stamina.
	void RestoreStamina();

	// Function called when player spawns to reset anything necessary.
	void SpawnReset();

	void KillVoice();

	// Function When enemy is in range of takedown.
	UFUNCTION()
	void OnEnemyOverlap(AActor* Enemy);

	// Function When enemy is out of range of takedown.
	UFUNCTION()
	void OnEnemyEndOverlap(AActor* Enemy);

private:

	// Reference to enemy in range of takedown.
	class AEnemy* TargetEnemy;

	// Reference to enemy player is attacking.
	class AEnemy* KillingEnemy;

	// Reference to enemy that is attacking player.
	class AEnemy* AttackingEnemy;

	// Reference to current weapon in hand.
	class AWeapon* CurrentWeapon;

	// Timer Handle for Sprinting.
	FTimerHandle SprintTime;

	// Timer Handle for Spawning.
	FTimerHandle SpawnTime;

	FTimerHandle KillTime;

	// Vector variable for start positon for functions Start Attack and Start Turn.
	FVector StartPosition;

	// Vector variable for end positon for functions Start Attack and Start Turn.
	FVector EndPosition;

	// Rotator variable for start rotation for functions Start Attack and Start Turn.
	FRotator StartRot;

	// Rotator variable for end rotation for functions Start Attack and Start Turn.
	FRotator EndRot;

	// Bool variable to check if player can sprint
	bool bCanSprint;

	// Bool variable to check when player is sprinting.
	bool bSprinting;

	// Bool variable to check when player is attacking
	bool bAttacking;

	// Bool variable to check when player is turning
	bool bIsTurning;

	// Bool variable to check if the timer function has played.
	bool bTimerPlayed;

	bool bSprintSoundPlayed;

	// Bool variable to check if player can restore stamina
	bool bRestore;


	// Float variable to determine if player is moving. 
	float Movement;

	// Float variable for the start time of functions Start Attack and Start Turn.
	float StartTime;

	// Float variable for the end time of functions Start Attack and Start Turn.
	float EndTime;

	// Int Variable for the number of enemies player has killed.
	uint32 killCount;

};
