// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "AI/EnemyController.h"
#include "TargetPoints/Waypoint.h"
#include "BTTNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UBTTNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTNextWaypoint(const FObjectInitializer& ObjectInitializer);

	// Function that executes this task.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:

	// Function that gets the next waypoint.
	virtual AWaypoint* GetNextWaypoint(UBehaviorTreeComponent& OwnerComp);

};
