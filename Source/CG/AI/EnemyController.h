// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
		AEnemyController();

		/** Reference to the behavior tree */
		UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree;

		/** Behavior tree components*/
		UPROPERTY(EditDefaultsOnly)
		UBehaviorTreeComponent* BehaviorTreeComponent;

		/** Blackboard components */
		UPROPERTY(EditDefaultsOnly)
		UBlackboardComponent* BlackboardComponent;

		// Function for the controlled pawn.
		void Possess(APawn* Pawn);

};
