// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "BTTScream.generated.h"

/**
 * 
 */

////////////////////////Prototype - Not used In Game ///////////////////////////////////////////////////////////
UCLASS()
class CG_API UBTTScream : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTScream(const FObjectInitializer& ObjectInitializer);

	// Function that executes this task.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemeory);
	
};
