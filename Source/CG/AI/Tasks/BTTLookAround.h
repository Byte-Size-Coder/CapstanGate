// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "TargetPoints/MemoryLocation.h"
#include "Player/Eric.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "BTTLookAround.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UBTTLookAround : public UBTTaskNode
{
	GENERATED_BODY()
	
	
public:

	UBTTLookAround(const FObjectInitializer& ObjectInitializer);

	// Function that executes this task.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemeory);

};
