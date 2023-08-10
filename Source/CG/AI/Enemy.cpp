// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating pawnsensing components on enemy.
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent2 = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent2"));

	// Creating player's takedown position on enemy.
	TakedownPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("TakedownPosition"));
	TakedownPosition->AttachTo(RootComponent);
	
	// Attaching created function onto pawnsensing functionality.
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemy::OnSeePlayer);
	PawnSensingComponent2->OnSeePawn.AddDynamic(this, &AEnemy::OnSeePlayer);

	// Setting variables on enemy creation.
	bSeesPlayer = false;

	bKilledPlayer = false;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If enemy can see the player.
	if (bSeesPlayer)
	{
		if (PawnSensingComponent && Player)
		{
			// Gets the distance between player and enemy.
			float Dist = FVector::Dist(Player->GetActorLocation(), GetActorLocation());
			// If the enemy still has a line of sight of the player and is in distance, create a memory location of where the player is.
			if (PawnSensingComponent->HasLineOfSightTo(Player) && Dist <= 1000.0f)
			{
				// Set the enemy memory location of the player to the player.
				SetMemoryLocation(Player->GetActorLocation());
			}
			else
			{
				// Enemy does not see player
				bSeesPlayer = false;

				// Get refence to enemy controller. 
				AEnemyController* Controller = Cast<AEnemyController>(GetController());

				// Change blackboard values accordingly.
				if (Controller)
				{
					Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSeePlayer"), false);
					Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSawPlayer"), true);
				}

				// Call player function to update player's status.
				Player->Seen();
				
			}
		}
	}
	// If Enemy is attacking player, use Interpolation to smoothly turn enemy to face the player.
	if (bIsAttacking)
	{
		float Time = GetWorld()->TimeSeconds - StartTime;
		float Percent = Time / EndTime;

		FRotator EnemyRot = FRotationMatrix::MakeFromX(Player->GetActorLocation() - GetActorLocation()).Rotator();
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), EnemyRot, Percent, 2.0f));

		if (Percent >= 1.0)
		{
			bIsAttacking = false;
		}
	}
	// If enemy is turning, use Interpolation to smoothly turn enemy to face a certain way. 
	if (bIsTurning)
	{
		float Time = GetWorld()->TimeSeconds - StartTime;
		float Percent = Time / EndTime;


		SetActorRotation(FMath::RInterpTo(StartRotation, EndRotation, Percent, 2.0f));

		if (Percent >= 1.0)
		{
			bIsTurning = false;
		}
	}
}

void AEnemy::OnSeePlayer(APawn* Pawn)
{
	// Get refence to enemy controller. 
	AEnemyController* Controller = Cast<AEnemyController>(GetController());

	if (Controller)
	{
		// Check if what the enemy sees is the player.
		 Player = Cast<AEric>(Pawn);

		if (Player)
		{
			// Set the enemy to engage the player and set the enemy's memory to player's location
			Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), Pawn);

			bEngaged = true;

			GetCharacterMovement()->MaxWalkSpeed = EngagedSpeed;

			SetMemoryLocation(Player->GetActorLocation());
	
			
			// Set the blackboard value of the memory locator to the enemy's player memory.
			Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Memory"), PlayerMemory);
			Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSeePlayer"), true);

			// Enemy is alerted and sees the player.
			bAlert = true;
			bSeesPlayer = true;
			bSawPlayer = true;

			// Call player function to update player's status.
			Player->Seen();	
		}
	}
}

void AEnemy::SetMemoryLocation(FVector Location)
{
	// If there is no PlayerMemory created, Create and spawn one into the world and set location.
	if (!PlayerMemory)
	{
		PlayerMemory = GetWorld()->SpawnActor<AMemoryLocation>(MemoryClass, Location, Location.Rotation());
	}
	// If there is one created, set the location.
	else
	{
		PlayerMemory->SetActorLocation(Location);
	}
}

void AEnemy::StartTurn(FRotator TargetRotation, float Duration)
{
	// Enemy is now turning.
	bIsTurning = true;

	// Set the Start and end time for this function.
	StartTime = GetWorld()->TimeSeconds;
	EndTime = Duration;

	// Set the start and end rotations for this function.
	StartRotation = GetActorRotation();
	EndRotation = TargetRotation;
}

void AEnemy::StartAttack(FVector StartLoc, FVector EndLoc, float Duration)
{
	// Enemy is now attacking.
	bIsAttacking = true;

	// Set the Start and end time for this function.
	StartTime = GetWorld()->TimeSeconds;
	EndTime = Duration;

	// Set the start and end positions for this function.
	StartPosition = StartLoc;
	EndPosition = EndLoc;

	// Set the start and end rotations for this function using calculations.
	FVector Dir = (EndLoc - StartLoc);

	Dir.Normalize();

	StartRotation = GetActorRotation();

	EndRotation = Dir.Rotation();
}

void AEnemy::KillPlayer()
{
	// Get reference to the player.
	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		// If player has a current spawn point, spawn player there.
		if (Player->CurrentSpawnPoint)
		{
			Player->SpawnPlayer();
		}
		else
		{
			// Destroy the player.
			Player->Destroy();
		}
	}
	
}

void AEnemy::ResetEnemy()
{
	// Change enemy's speed to the patrol speed
	GetCharacterMovement()->MaxWalkSpeed = GetPatrolSpeed();

	// Get reference to enemy controller
	AEnemyController* Controller = Cast<AEnemyController>(GetController());

	// Reset all the enemies stats to its patrol state.
	bAlert = false;

	bEngaged = false;

	if (Controller)
	{
		Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), NULL);
		Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSeePlayer"), false);
		Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSawPlayer"), false);
		Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bScream"), true);
		Controller->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bTakeDown"), false);
	}

	// Call player function to update player's status.

	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (Player)
	{
		Player->Seen();
	}
}


//////////////////////////////////////////////////Getters and Setters/////////////////////////////////////////////////
int32 AEnemy::GetPatrolPattern()
{
	return PatrolPattern;
}

float AEnemy::GetPatrolSpeed()
{
	return PatrolSpeed;
}

float AEnemy::GetEngagedSpeed()
{
	return EngagedSpeed;
}


float AEnemy::GetWanderSpeed()
{
	return WanderSpeed;
}

bool AEnemy::CanSeePlayer()
{
	return bSeesPlayer;
}

bool AEnemy::IsAlert()
{
	return bAlert;
}

bool AEnemy::HasSeenPlayer()
{
	return bSawPlayer;
}

bool AEnemy::HasKilledPlayer()
{
	return bKilledPlayer;
}

void AEnemy::SetPatrolPattern(int32 Patrol)
{
	PatrolPattern = Patrol;
}

void AEnemy::SetSawPlayer(bool Saw)
{
	bSawPlayer = Saw;
}

void AEnemy::SetKilledPlayer(bool Kill)
{
	bKilledPlayer = Kill;
}


