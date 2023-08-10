// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/EnemyController.h"
#include "AI/Enemy.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTFaceForward.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UBTTFaceForward : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTFaceForward(const FObjectInitializer& ObjectInitializer);

	// Function that executes this task.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
	
};
