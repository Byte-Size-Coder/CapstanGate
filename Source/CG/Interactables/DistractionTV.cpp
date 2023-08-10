// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "Player/Eric.h"
#include "DistractionTV.h"


// Sets default values
ADistractionTV::ADistractionTV()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a root component for the actor.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Create a mesh and attach it to root component.
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
	Mesh->SetMaterial(0, OffMaterial);

	// Create Reference to location and attach to root component
	Spot = CreateDefaultSubobject<USceneComponent>(TEXT("Spot"));
	Spot->AttachTo(RootComponent);

	// Create 
	AudioComponent = CreateAbstractDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->AttachTo(RootComponent);

	// Set variable to indicate tv is off.
	bIsOn = false;
	
}

// Called when the game starts or when spawned
void ADistractionTV::Interact()
{
	// If TV is not on
	if (!bIsOn)
	{
		// Set sound and material to indicate tv is now on.
		AudioComponent->SetSound(TVOnSound);
		AudioComponent->Play();

		Mesh->SetMaterial(1, OnMaterial);

		// Create a sphere raycast around the TV.
		FCollisionQueryParams TraceParams(FName(TEXT("EnemyTrace")), true, this);
		
		TArray<FOverlapResult> Hits;

		GetWorld()->OverlapMultiByChannel(Hits, GetActorLocation(), FQuat::Identity, COLLISION_ENEMY, FCollisionShape::MakeSphere(TvToEnemyDist), TraceParams);

		// Go through all the objects that it hits.
		for (FOverlapResult Result : Hits)
		{
			// Get reference to the enemy and enemy controller.
			AEnemy* Enemy = Cast<AEnemy>(Result.Actor.Get());


			if (Enemy)
			{
				// Get reference to enemy controller.
				AEnemyController* EnemyController = Cast<AEnemyController>(Enemy->GetController());

				// Set engage to true and set engage speed.
				Enemy->bEngaged = true;

				Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetEngagedSpeed();

				// Get Reference to the player.
				AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				// If the enemy can not see the player
				if (!Enemy->CanSeePlayer())
				{
					// Get Navigation system from the world.
					UNavigationSystem* Nav = GetWorld()->GetNavigationSystem();

					// Get player's and enemy's location.
					FVector PlayerLocation = Player->GetActorLocation();

					FVector EnemyLocation = Enemy->GetActorLocation();

					// Create necessary variables (A vector point, advance indicator for loop, and counter).
					FVector RunPoint;

					bool bAdvance = false;

					int Count = 0;

					// Continue loop if advance remains false or the counter is less then 10.
					while (!bAdvance && Count <= 10)
					{
						// Set RunPoint location around the scene component spot.
						RunPoint.X = Spot->GetComponentLocation().X + FMath::FRandRange(-200, 200);
						RunPoint.Y = Spot->GetComponentLocation().Y + FMath::FRandRange(-200, 200);
						RunPoint.Z = Spot->GetComponentLocation().Z;

						if (Nav)
						{
							// Create a path findy query and set its parameters.
							FPathFindingQuery QueryParams;
							QueryParams.StartLocation = EnemyLocation;
							QueryParams.EndLocation = RunPoint;
							QueryParams.NavData = Nav->GetMainNavData();
							QueryParams.Owner = Enemy;
							QueryParams.SetAllowPartialPaths(false);

							// If there is a valid path from start to end.
							if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
							{
								// Set enemy's memory location to the runpoint created.
								Enemy->SetMemoryLocation(RunPoint);

								// Set neccesary blackboard variables.
								if (EnemyController)
								{
									EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), Player);
									EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Memory"), Enemy->PlayerMemory);
								}

								// Set advance to true.
								bAdvance = true;

							}
							// If there is no valid path.
							else
							{
								// add 1 to the counter.
								Count++;
							}
						}
					}
				}
			}
		}

		// Set variable to indicate tv is on. 
		bIsOn = true;

		// Set timer to eventually turn off the tv.
		GetWorld()->GetTimerManager().SetTimer(OnTime, this, &ADistractionTV::TurnOff, 7.0f, false);
	}
	
}

void ADistractionTV::TurnOff()
{
	// Play sound and set material, tv is now off
	AudioComponent->SetSound(TVOffSound);
	AudioComponent->Play();
	Mesh->SetMaterial(0, OffMaterial);
	
	// Set variable to indicate tv is off.
	bIsOn = false;
}



