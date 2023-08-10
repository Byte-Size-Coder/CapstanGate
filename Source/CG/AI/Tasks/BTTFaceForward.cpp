// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BTTFaceForward.h"



UBTTFaceForward::UBTTFaceForward(const FObjectInitializer& ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTFaceForward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// If there is no world, the execution fails.
	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	// Get reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("SelfActor")));

	// Get reference to the enemy's current waypoint
	AWaypoint* CurrentWaypoint = Cast<AWaypoint>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Waypoint")));

	// Call the StartTurn function on enemy to rotate smoothly forward from waypoint.
	Enemy->StartTurn(CurrentWaypoint->GetActorRotation(), 0.5f);

	return EBTNodeResult::Succeeded;
}
