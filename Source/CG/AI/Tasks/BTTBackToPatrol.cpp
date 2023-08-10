// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"
#include "BTTBackToPatrol.h"



UBTTBackToPatrol::UBTTBackToPatrol(const FObjectInitializer& ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTBackToPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// If there is no world, the execution fails.
	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}
	
	// Create a reference tho the enemy's controller
	AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetOwner());

	// Create a reference to the enemy by grabbing the pawn controlling the enemy controller.
	AEnemy* Enemy = Cast<AEnemy>(EnemyController->GetPawn());

	// Reset Enemy's stats to return him to patrol.
	Enemy->ResetEnemy();

	return EBTNodeResult::Succeeded;
}

