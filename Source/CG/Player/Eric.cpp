// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Interactables/InteractableItem.h"
#include "Interactables/InteractableItemWeapon.h"
#include "Interactables/InteractableItemUtility.h"
#include "Interactables/DistractionTV.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Weapons/Weapon.h"
#include "AI/Enemy.h"
#include "UI/EricHUD.h"
#include "Eric.h"


// Sets default values.
AEric::AEric()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 91.0f);

	// set our turn rates for input.
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// setting walk and sprint speed for the character.
	WalkSpeed = 500;
	SprintSpeed = 800;

	// Create a CameraComponent.
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCamera->AttachParent = GetCapsuleComponent();
	FPCamera->RelativeLocation = FVector(0, 0, 64.f); // Position the camera.
	FPCamera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn).
	MeshArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshArms"));
	MeshArms->SetOnlyOwnerSee(true);
	MeshArms->AttachParent = FPCamera;
	MeshArms->bCastDynamicShadow = false;
	MeshArms->CastShadow = false;

	// Create a Sphere collider for takedown range.
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->AttachTo(RootComponent);

	// Create audio component for movement.
	MovementAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Movement Audio Component"));
	MovementAudioComponent->AttachTo(RootComponent);

	// Create audio component for voice cues.
	VocalAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Vocal Audio Component"));
	VocalAudioComponent->AttachTo(RootComponent);

	// Create an inventory component.
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	// Enables the ability for character to crouch.
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	// sets the character to walk speed on creation.
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Attach ActorOverlap functionality to custom functions
	OnActorBeginOverlap.AddDynamic(this, &AEric::OnEnemyOverlap);
	OnActorEndOverlap.AddDynamic(this, &AEric::OnEnemyEndOverlap);

	/** Set initial values to variable upon creation **/
	bIsCrouching = false;

	bInVent = false;

	bHasKnife = false;

	bPickUp = false;

	bPickUpKnife = false;

	bIsSeen = false;

	bAlerted = false;

	bAttacking = false;

	bHUDButtonDown = false;

	bAttacked = false;

	bRestore = false;

	bTimerPlayed = false;

	bSprintSoundPlayed = false;

	bRemotetut = true;

	bScrewdrivertut = true;

	bKnifetut = true;

	//bKillVoices = true;

	Stamina = 100.0f;

	killCount = 0;

	CurrentSpawnPoint = NULL;

}

void AEric::Tick(float DeltaTime)
{
	// Set the movment variable by checking player's velocity
	Movement = GetCharacterMovement()->Velocity.Size();

	// If player is sprinting.
	if (bSprinting)
	{
		// if player's stamins is less or equal to 0, end his sprint.

		if (!bCanSprint)
		{
			EndSprint();
		}

		if (Stamina <= 0.0f)
		{
			EndSprint();

			if (!bSprintSoundPlayed)
			{
				MovementAudioComponent->SetSound(OutOfBreathSound);
				MovementAudioComponent->Play();

				bSprintSoundPlayed = true;
			}
		}

		// If player is not moving, or is crouched (stopped sprinting).
		if (Movement <= 0.0f || bIsCrouching)
		{
			// Stop the sprinting camera shake and play the end run camera shake.
			APawn* PawnOwner = Cast<APawn>(GetOwner());
			if (RunCameraShake && EndRunCameraShake)
			{
				APlayerController* EricController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

				if (EricController)
				{
						EricController->ClientStopCameraShake(RunCameraShake);
						EricController->ClientPlayCameraShake(EndRunCameraShake, 0.1f);
				}
			}

			// Switch sprinting to false
			bSprinting = false;
		}
		else
		{
			// Drain stamina while player is sprinting. 
			Stamina -= 0.5f;

			if (Stamina < 0.0f)
			{
				Stamina = 0.0f;
			}
		}
	}
	else
	{
		// Set timer to restore player's stamina if needed.
		if (Stamina < 100.0f)
		{
			if (!bTimerPlayed)
			{
				GetWorld()->GetTimerManager().SetTimer(SprintTime, this, &AEric::RestoreStamina, 3.0f, false);
				bTimerPlayed = true;
			}
		}
	}

	// Smooth move to attack the enemy.
	if (bAttacking)
	{
		float Time = GetWorld()->TimeSeconds - StartTime;
		float Percent = Time / EndTime;
		

		SetActorLocation(FMath::VInterpTo(StartPosition, EndPosition, Percent, AttackSpeed));
		FRotator PlayerRot = FRotationMatrix::MakeFromX(KillingEnemy->GetActorLocation() - GetActorLocation()).Rotator();
		GetController()->SetControlRotation(FMath::RInterpTo(GetActorRotation(), PlayerRot, Percent, AttackSpeed));

		if (Percent >= 1.0)
		{
			bAttacking = false;
		}
	
		
	}
	// Smooth turn for player.
	if (bIsTurning)
	{
		float Time = GetWorld()->TimeSeconds - StartTime;
		float Percent = Time / EndTime;

		FRotator EnemyRot = FRotationMatrix::MakeFromX(AttackingEnemy->GetActorLocation() - GetActorLocation()).Rotator();
		GetController()->SetControlRotation(FMath::RInterpTo(GetActorRotation(), EnemyRot, Percent, TurnSpeed));
		
		if (Percent >= 1.0)
		{
			bIsTurning = false;
		}

	}
	// Restoring stamina.
	if (bRestore)
	{
		Stamina += (1.0f);
		if (bSprinting)
		{
			bRestore = false;
			bTimerPlayed = false;
		}

		if (Stamina >= 100.0f)
		{
			Stamina = 100.0f;
			bRestore = false;
			bTimerPlayed = false;
		}

		if (bSprintSoundPlayed)
		{ 
			MovementAudioComponent->Stop();
			bSprintSoundPlayed = false;
		}
	}
}


// Called to bind functionality to input.
void AEric::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings.
	check(InputComponent);

	// Crouch Action.
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AEric::ToggleCrouch);

	//Sprint Actions.
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AEric::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AEric::EndSprint);

	//Interact Action.
	InputComponent->BindAction("Interact", IE_Pressed, this, &AEric::OnInteract);
	InputComponent->BindAction("UseRemote", IE_Pressed, this, &AEric::UseRemote);

	//Display HUD
	InputComponent->BindAction("ShowHUD", IE_Pressed, this, &AEric::ToggleHUD);
	InputComponent->BindAction("ShowHUD", IE_Released, this, &AEric::ToggleHUD);

	//TakeDown Action.
	InputComponent->BindAction("TakeDown", IE_Pressed, this, &AEric::TakeDown);

	// Character movement.
	InputComponent->BindAxis("Forward", this, &AEric::MoveForward);
	InputComponent->BindAxis("Right", this, &AEric::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick.
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AEric::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AEric::LookUpAtRate);
}

//////////////////////////////////////////////////////////Movement Functions////////////////////////////////////////////////////////////
void AEric::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction.
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AEric::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction.
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AEric::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information.
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEric::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information.
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AEric::ToggleCrouch()
{
	// Check if player is in the vent or not.
	if (!bInVent)
	{
		// If we are crouching then CanCrouch will return false. If we cannot crouch then calling Crouch() wont do anything.  
		if (CanCrouch() == true)
		{
			Crouch();
			bIsCrouching = true;
			MovementAudioComponent->Stop();
		}
		else
		{
			UnCrouch();
			bIsCrouching = false;
			
		}
	}
}

void AEric::StartSprint()
{
	// If player can sprint and player's stamina is less greater then 0
	if (bCanSprint && Stamina > 0.0f)
	{

		if (bIsCrouching)
		{
			ToggleCrouch();
		}

		// Change speed to sprint speed.
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

		

		// Play the RunCamera shake.
		if (RunCameraShake)
		{
			APlayerController* EricController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

			if (EricController)
			{
				if (!bIsCrouching)
				{
					EricController->ClientPlayCameraShake(RunCameraShake, 1.0f);
					bSprinting = true;
				}
			}
		}
	}
}

void AEric::EndSprint()
{
	// Change speed to walk speed.

	if (!bInVent)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}


	// If player is still sprinting.
	if (bSprinting)
	{
		// Stop Run camera shake and play EndRun camera shake, player has stopped sprinting.
		if (RunCameraShake && EndRunCameraShake)
		{
			APlayerController* EricController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

			if (EricController)
			{
				if (!bIsCrouching)
				{
					EricController->ClientStopCameraShake(RunCameraShake);
					EricController->ClientPlayCameraShake(EndRunCameraShake, 0.1f);
				}
			}
		}
		bSprinting = false;
	}
}

void AEric::RestoreStamina()
{
	// Set so player is allow to restore their stamina.
	bRestore = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////Interaction Functions///////////////////////////////////////////////////////
void AEric::OnInteract()
{
	//Cast a sphere to see if any Interactables are in range.
	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, this);

	TArray<FOverlapResult> Hits;
	GetWorld()->OverlapMultiByChannel(Hits, GetActorLocation(), FQuat::Identity, COLLISION_INTERACTABLE, FCollisionShape::MakeSphere(InteractionRadius), TraceParams);


	AInteractableItem* Item = NULL;
	float minDistance = MAX_FLT;

	//If there are interactable items, check to see which one is the closest and interact with that item.
	for (FOverlapResult Result : Hits)
	{
		AInteractableItem* CurrentInteractableItem = Cast<AInteractableItem>(Result.Actor.Get());
		float Dist = FVector::Dist(CurrentInteractableItem->GetActorLocation(), GetActorLocation());

		if (Dist < minDistance)
		{
			Item = CurrentInteractableItem;
			minDistance = Dist;
		}
	}
	// If there is an item, interact with it.
	if (Item)
	{
		if (!Item->Interact(this))
		{
			// Handle Failure. 
		}
	}
}

void AEric::EquipWeapon(AInteractableItemWeapon* WeaponPickup)
{
	// If there is a current weapon, remove it and place it where the pickup item is.
	if (CurrentWeapon)
	{
		GetWorld()->SpawnActor<AInteractableItemWeapon>(CurrentWeapon->GetInteractableWeaponClass(), WeaponPickup->GetActorLocation(), WeaponPickup->GetActorRotation());
		CurrentWeapon->Destroy();
		CurrentWeapon = NULL;
	}

	//Spawn weapon player is picking up into his hands.
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponPickup->GetWeaponClass(), SpawnParameters);
	CurrentWeapon->AttachRootComponentTo(MeshArms, TEXT("bn_r_index1"));
	VocalAudioComponent->SetSound(EquipKnifeSound);
	VocalAudioComponent->Play();
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (HUD)
	{
		HUD->DisplayHUD();
		HUD->IconWidget->GetKnifeImage()->SetOpacity(1.0f);
	}
	bHasKnife = true;

	ShowKnifeTutorial();
	//GetWorld()->GetTimerManager().SetTimer(KillTime, this, &AEric::KillVoice, 20.0f, false);
}

void AEric::RemoveWeapon()
{
	// If player has a current weapon, destroy it.
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = NULL;
	}
}


void AEric::UseRemote()
{
	// If player has remote in inventory.
	if (Inventory->Contains(REMOTE))
	{
		// Create a sphere raycast around the player.
		FCollisionQueryParams TraceParams(FName(TEXT("TVTrace")), true, this);

		TArray<FOverlapResult> Hits;
		GetWorld()->OverlapMultiByChannel(Hits, GetActorLocation(), FQuat::Identity, COLLISION_TV, FCollisionShape::MakeSphere(RemoteToTvDist), TraceParams);

		// Go through all the objects that it hits.
		for (FOverlapResult Result : Hits)
		{
			// Check if it is the TV.
			ADistractionTV* TV = Cast<ADistractionTV>(Result.Actor.Get());

			// Interact with TV.
			TV->Interact();
		}
	}
}

void AEric::DisablePlayerInput()
{
	// Disable input from player to let the attack playout.
	GetController()->StopMovement();
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void AEric::EnablePlayerInput()
{
	// Enable input to the player.
	EnableInput(GetWorld()->GetFirstPlayerController());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////Attack Functions//////////////////////////////////////////////////////////////////////////////////


void AEric::OnEnemyOverlap(AActor* Enemy)
{
	// Store the reference to the enemy that is in range.
	AEnemy* EnemyCharacter = Cast<AEnemy>(Enemy);
	if (EnemyCharacter)
	{
		TargetEnemy = EnemyCharacter;

		if (CurrentWeapon && TargetEnemy && !bIsSeen && !bInVent)
		{
			AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

			if (HUD)
			{
				HUD->ShowTakeDownText();
			}
		}
	}
}

void AEric::OnEnemyEndOverlap(AActor* Enemy)
{
	// Remove the reference to the enemy that went out of range.
	AEnemy* EnemyCharacter = Cast<AEnemy>(Enemy);
	if (EnemyCharacter)
	{
		TargetEnemy = NULL;


		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (HUD)
		{
			if (!bIsSeen && CurrentWeapon)
			{
				HUD->HideTakeDownText();
			}
		}
	}
}

void AEric::StartAttack(FVector StartLoc, FVector EndLoc, float Duration)
{
	// Player is now attacking.
	bAttacking = true;

	// Get the start time and end time of this function.
	StartTime = GetWorld()->TimeSeconds;
	EndTime = Duration;

	// Get the Start position (Player) and end position (Takedown position on enemy).
	StartPosition = StartLoc;
	EndPosition = EndLoc;
}

void AEric::TakeDown()
{

	// If there is an enemy in range, and player has a weapon.
	if (TargetEnemy && CurrentWeapon)
	{
		AEnemyController* EnemyController = Cast<AEnemyController>(TargetEnemy->GetController());

	// If player is not seen.
		if (!bIsSeen && !bInVent)
		{
			// Set the enemy in range as the attacking enemy.
			KillingEnemy = TargetEnemy;

			// Turn off enemy's collision so player can interact.
			KillingEnemy->SetActorEnableCollision(false);

			// If player is crouching, make them stand.
			if (bIsCrouching)
			{
				ToggleCrouch();
			}

			EndSprint();

			// Perform attack function.
			StartAttack(GetActorLocation(), KillingEnemy->TakedownPosition->GetComponentLocation(), 0.5f);

			// Set takedown to true for player  takedown animation.
			bTakeDown = true;

			// Set enemies blackboard and behavior tree for when they are being attacked.
			EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bTakeDown"), true);

			// Pick a random takedown move to perform and play specific animations for player and enemy.
			TakeDownMove = FMath::RandRange(1, 2);

			// Pair the takedown move from player to enemy so they both play correct animations.
			EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Int>(TEXT("TakeDownMove"), TakeDownMove);

			// Stop any movement sounds from player
			MovementAudioComponent->Stop();

			// Disable input from player to let the attack playout.
			GetController()->StopMovement();
			DisableInput(GetWorld()->GetFirstPlayerController());

		}
	}
}

void AEric::KillEnemy()
{
	// Spawn Particle at enemies location
	UGameplayStatics::SpawnEmitterAtLocation(KillingEnemy, KillingEnemy->DeathParticle, KillingEnemy->GetActorLocation(), KillingEnemy->GetActorRotation());

	// Notify enemies spawnpoint that enemy is killed.
	if (KillingEnemy->SpawnPoint)
	{
		KillingEnemy->SpawnPoint->bIsSpawned = false;
	}

	// Destroy enemy.
	KillingEnemy->Destroy();
	KillingEnemy = NULL;

	// Add 1 to the kill count.
	killCount += 1;

	// Play appropiate vocal for specific kills
	switch (killCount)
	{
	default:
		break;
	case 1:
		VocalAudioComponent->SetSound(FirstKillVocal);
		VocalAudioComponent->Play();
		break;
	case 3:
		VocalAudioComponent->SetSound(ThirdKillVocal);
		VocalAudioComponent->Play();
		break;
	case 5:
		VocalAudioComponent->SetSound(FifthKillVocal);
		VocalAudioComponent->Play();
		break;
	case 7:
		VocalAudioComponent->SetSound(SeventhKillVocal);
		VocalAudioComponent->Play();
		break;
	case 10:
		VocalAudioComponent->SetSound(TenthKillVocal);
		VocalAudioComponent->Play();
		break;
	}
	// Enable input to the player.
	EnableInput(GetWorld()->GetFirstPlayerController());

	// Player is now finish attacking
	bAttacking = false;

	// Call to check if player is seen or alerted again. 
	Seen();

	/*
	if (bKillVoices)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(KillTime))
		{
			GetWorld()->GetTimerManager().ClearTimer(KillTime);
		}

		GetWorld()->GetTimerManager().SetTimer(KillTime, this, &AEric::KillVoice, 20.0f, false);
	}
	*/
}

/*
void AEric::KillVoice()
{
	VocalAudioComponent->SetSound(NoKillVocal);
	VocalAudioComponent->Play();
	GetWorld()->GetTimerManager().SetTimer(KillTime, this, &AEric::KillVoice, 20.0f, false);
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////Detection-Death Functions/////////////////////////////////////////////////////////////


void AEric::Seen()
{
	// Create seen counter.
	int SeenCount = 0;

	// Create alert counter
	int AlertCount = 0;

	// Get reference to player's HUD.
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// For ever enemy in the world.
	for (TActorIterator<AEnemy> EnemyItr(GetWorld()); EnemyItr; ++EnemyItr)
	{
		AEnemy* Enemy = Cast<AEnemy>(*EnemyItr);

		if (Enemy)
		{
			// If enemy can see player, add one to seen count.
			if (Enemy->CanSeePlayer())
			{
				SeenCount++;
			}
			// If enemy is looking for player, add one to alert count. 
			if (Enemy->IsAlert())
			{
				AlertCount++;
			}
		}
	}

	// If seen count is greater then 0, player is seen and can sprint. 
	if (SeenCount > 0 )
	{
		bIsSeen = true;
		bCanSprint = true;

		HUD->HideTakeDownText();
	
	// Play apporpriate HUD animation to indicate player is seen.
		if (!HUD->bSeenDo)
		{
			if (HUD->bAlertDo)
			{
				HUD->ShowFearWidget2();
			}
			else
			{
				HUD->ShowFearWidget();
			}
		}
	}
	// If seen count is 0, player is not seen.
	else
	{
		if (AlertCount > 0)
		{
			// Hide indication that player is seen. 
			if (HUD->bSeenDo)
			{
				HUD->HideFearWidget2();
			}
		}
		
		bIsSeen = false;
		//GetWorld()->GetTimerManager().SetTimer(SprintTime, this, &AEric::SprintCheck, 2.0f, false);
	}
	// If alert count is greater then 0, player is alerted (and possibly seen).
	if (AlertCount > 0)
	{
		bAlerted = true;
		bCanSprint = true;
	}
	else
	{
	// Player is not seen or alerted, player can not sprint anymore.
		bAlerted = false;
		bCanSprint = false;

	// Hide indication that player is alerted.
		if (HUD->bAlertDo)
		{
			HUD->HideFearWidget();
		}
	}
}


void AEric::LookAndLock(AEnemy* Target)
{
	// If player is attacking another enemy, enemy is free and player stops attacking.
	if (bAttacking)
	{
		AEnemyController* EnemyC = Cast<AEnemyController>(KillingEnemy->GetController());

		if (EnemyC)
		{
			EnemyC->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bTakeDown"), false);
		}

		bAttacking = false;
	}

	/*
	if (bIsCrouching)
	{
		ToggleCrouch();
	}
	*/

	// Player is now being attacked.
	bAttacked = true;

	// Get reference to the attacking enemy.
	AttackingEnemy = Target;

	// Get the player to turn smoothly to look at enemy.
	StartTurn(GetActorLocation(), Target->GetActorLocation(), 0.5f);

	// Stop player movement and disable input.
	GetController()->StopMovement();
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void AEric::StartTurn(FVector StartLoc, FVector EndLoc, float Duration)
{
	// Player is turning.
	bIsTurning = true;

	// Get the start and end time of this function.
	StartTime = GetWorld()->TimeSeconds;
	EndTime = Duration;

	// Get the start position (Player) and end position (enemy).
	StartPosition = StartLoc;
	EndPosition = EndLoc;

	// Get the start and end rotation through some calculations.
	FVector Dir = (EndLoc - StartLoc);

	Dir.Normalize();

	StartRot = GetActorRotation();

	FRotator PlayerRot = FRotationMatrix::MakeFromX(EndLoc - StartLoc).Rotator();

	EndRot = PlayerRot;
}

void AEric::SpawnPlayer()
{
	// Remove reference to attacking enemy.
	AttackingEnemy = NULL;

	// Set player's location and rotation to current spawn point.
	SetActorLocation(CurrentSpawnPoint->GetActorLocation());

	GetController()->SetControlRotation(CurrentSpawnPoint->GetActorRotation());

	CurrentSpawnPoint->SpawnCheck();
	CurrentSpawnPoint->SpawnEnemies();

	// Get reference to the player's HUD
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Play HUD animation for player spawn.
	if (HUD)
	{
		HUD->HideDeathWidget();
	}
	
	// Set timer to wait before reseting player's stats. 
	GetWorld()->GetTimerManager().SetTimer(SpawnTime, this, &AEric::SpawnReset, 1.0f, false);
	
}

void AEric::SpawnReset()
{
	// Set player's speed to walk speed.
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// If Player was sprinting, stop and do not allow player to sprint.
	if (bSprinting)
	{
		bSprinting = false;
	}

	bCanSprint = false;

	// Player is not being attacked anymore.
	bAttacked = false;

	// Enable player input.
	EnableInput(GetWorld()->GetFirstPlayerController());

	// Get reference to player's HUD.
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Remove HUD Indicators. 
	if (HUD)
	{
		HUD->HideFearWidget2();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////Misc Functions///////////////////////////////////////////////////////////////////////////


void AEric::ToggleHUD()
{
	// Get Reference to Player's HUD.
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Shows player's Inventory HUD.
	if (HUD)
	{
		HUD->DisplayHUD();
	}	
}


void AEric::ShowDeathWidget()
{
	// Get Reference to Player's HUD.
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Plays the animation on HUD for when player dies.
	if (HUD)
	{
		HUD->ShowDeathWidget();
	}
}

void AEric::ShowBloodSplatterWidget()
{
	// Get Reference to Player's HUD.
	AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Plays HUD animation to show blood splatters on attack. 
	if (HUD)
	{
		HUD->ShowBloodSplatterWidget();
	}
}






