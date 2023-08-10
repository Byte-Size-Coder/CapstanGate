// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"

#include "EnemyController.h"



AEnemyController::AEnemyController()
{
	// Creates both behavior tree and blackboard components.
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AEnemyController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
	// Initialize the blackboard components and starts the behavior tree. Also sets the first waypoint for the enemy. 
	if (Pawn)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*BehaviorTree);

		AEnemy* Enemy = Cast<AEnemy>(Pawn);

		if (Enemy->bEndEnemy)
		{
			AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSeePlayer"), true);
			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSawPlayer"), true);
			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bScream"), true);

			Enemy->SetMemoryLocation(Player->GetActorLocation());

			Enemy->bEngaged = true;

			Enemy->GetCharacterMovement()->MaxWalkSpeed = Enemy->GetEngagedSpeed();

			BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("SelfActor"), Enemy);
			BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), Player);
		}
		else
		{
			BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("SelfActor"), Enemy);
			BlackboardComponent->SetValue<UBlackboardKeyType_Int>(TEXT("PatrolPattern"), Enemy->GetPatrolPattern());

			if (Enemy->FirstWaypoint)
			{
				BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Waypoint"), Enemy->FirstWaypoint);
				BlackboardComponent->SetValue<UBlackboardKeyType_Float>(TEXT("WaitTime"), Enemy->FirstWaypoint->WaitTime);
				BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bDoSomething"), Enemy->FirstWaypoint->bDoSomething);
			}
			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bTakeDown"), false);
			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSeePlayer"), false);
			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bSawPlayer"), false);
			BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bScream"), true);
		}
	}
}
