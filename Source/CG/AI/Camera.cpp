// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "Camera.h"

////////////////////////Prototype - Not used In Game ///////////////////////////////////////////////////////////

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a root component for the actor.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Creates a mesh and attaches it to root component.
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	// Creating pawnsensing component on Camera.
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	// Attaching created function onto pawnsensing functionality.
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ACamera::OnSeePlayer);


}

void ACamera::BeginPlay()
{
	bSeesPlayer = false; 

	bMovingLeft = true;

	AnimationProgressDelegate.BindDynamic(this, &ACamera::AnimationProgress);
	AnimationFinishDelegate.BindDynamic(this, &ACamera::AnimationFinished);

	// Sets length of timeline.
	AnimationTimeline.SetTimelineLength(3.0f);

	// Tells which function to play when animation is finished.
	AnimationTimeline.SetTimelineFinishedFunc(AnimationFinishDelegate);

	// Adds a vector interpolation to the timeline.
	AnimationTimeline.AddInterpVector(AnimationCurve, AnimationProgressDelegate, TEXT("CameraOffset"));

	AnimationTimeline.PlayFromStart();

}

void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimationTimeline.TickTimeline(DeltaTime);
	
}

//When the Camera see the player
void ACamera::OnSeePlayer(APawn* Pawn)
{
	// Get refence to the player
	Player = Cast<AEric>(Pawn);

	// If player exist
	if (Player)
	{
		

		UE_LOG(LogTemp, Warning, TEXT("See Player"));

		AnimationTimeline.Stop();

		GetWorld()->GetTimerManager().SetTimer(WaitTime, this, &ACamera::Animate, 3.0f, false);
		
		// Create a sphere raycast around the Camera.
		FCollisionQueryParams TraceParams(FName(TEXT("EnemyTrace")), true, this);

		TArray<FOverlapResult> Hits;
		GetWorld()->OverlapMultiByChannel(Hits, GetActorLocation(), FQuat::Identity, COLLISION_ENEMY, FCollisionShape::MakeSphere(4000.0f), TraceParams);

		// go through all the objects that it hits.
		for (FOverlapResult Result : Hits)
		{

		// Get reference to enemy and enemy controller (if any).
			AEnemy* Enemy = Cast<AEnemy>(Result.Actor.Get());
			AEnemyController* EnemyController = Cast<AEnemyController>(Enemy->GetController());

			Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetEngagedSpeed();

			// If the enemy can not see the player.
			if (!Enemy->CanSeePlayer())
			{
				UNavigationSystem* Nav = GetWorld()->GetNavigationSystem();

				FVector PlayerLocation = Player->GetActorLocation();

				FVector EnemyLocation = Enemy->GetActorLocation();

				FVector TrackPoint;

				bool bAdvance = false;

				

					TrackPoint.X = PlayerLocation.X + FMath::FRandRange(-200, 200);
					TrackPoint.Y = PlayerLocation.Y + FMath::FRandRange(-200, 200);
					TrackPoint.Z = PlayerLocation.Z;

					if (Nav)
					{
						FPathFindingQuery QueryParams;
						QueryParams.StartLocation = EnemyLocation;
						QueryParams.EndLocation = TrackPoint;
						QueryParams.NavData = Nav->GetMainNavData();
						QueryParams.Owner = Enemy;
						QueryParams.SetAllowPartialPaths(false);

						if (Nav->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
						{
							UE_LOG(LogTemp, Warning, TEXT("VALID TRACK TO CAMERA"));
							Enemy->SetMemoryLocation(TrackPoint);
							EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), Player);
							EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Memory"), Enemy->PlayerMemory);
							bAdvance = true;
							
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("INVALID TRACK TO CAMERA"));
						}
					}
			}
		}
		
	}

}

void ACamera::AnimationProgress(FVector Value)
{
	// Rotates the door based on the animation timeline and curve.
	FRotator rotate = FRotator(0.0f * Value.X, 60.0f * Value.Y, 0.0f * Value.Z);
	SetActorRotation(rotate);
}

void ACamera::AnimationFinished()
{

	UE_LOG(LogTemp, Warning, TEXT("Animation finished"));

	if (bMovingLeft)
	{
		bMovingLeft = false;
	}
	else
	{
		bMovingLeft = true;
	}

	GetWorld()->GetTimerManager().SetTimer(WaitTime, this, &ACamera::Animate, 2.0f, false);

	
}

void ACamera::Animate()
{
	if (bMovingLeft)
	{
		AnimationTimeline.Play();
	}
	else
	{
		AnimationTimeline.Reverse();
	}

	UE_LOG(LogTemp, Warning, TEXT("Animation StartUp"));
}
