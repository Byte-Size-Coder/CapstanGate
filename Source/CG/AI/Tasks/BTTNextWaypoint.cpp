// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BTTNextWaypoint.h"


UBTTNextWaypoint::UBTTNextWaypoint(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// If there is no world, the execution fails.
	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	// Create a reference to the current waypoint and get the next one.
	AWaypoint* NextWaypoint = GetNextWaypoint(OwnerComp);

	// If there is no next waypoint, the execution fails.
	if (!NextWaypoint)
	{
		return EBTNodeResult::Failed;
	}

	// Set the current point to the next waypoint, the execution is a success.
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(TEXT("Waypoint"), NextWaypoint);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Float>(TEXT("WaitTime"), NextWaypoint->WaitTime);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(TEXT("bDoSomething"), NextWaypoint->bDoSomething);
	return EBTNodeResult::Succeeded;
}

AWaypoint* UBTTNextWaypoint::GetNextWaypoint(UBehaviorTreeComponent& OwnerComp)
{
	// Create a reference to the current waypoint for the enemy.
	AWaypoint * CurrentWaypoint = Cast<AWaypoint>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Waypoint")));

	// Access the next waypoint on the current one. 
	return CurrentWaypoint->NextWaypoint;
}

