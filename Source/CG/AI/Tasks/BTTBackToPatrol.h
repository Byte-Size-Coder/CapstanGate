// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/EnemyController.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTBackToPatrol.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UBTTBackToPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTBackToPatrol(const FObjectInitializer& ObjectInitializer);

	// Function that executes this task.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
	
};
