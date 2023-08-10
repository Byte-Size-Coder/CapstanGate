// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "NotifyScream.h"



void UNotifyScream::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// Get Reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(MeshComp->GetOwner());
	if (Enemy)
	{
		AEnemyController* EnemyController = Cast<AEnemyController>(Enemy->GetController());
		// Change blackboard variable to indicate enemy has screamed.
		if (EnemyController)
		{
			EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(TEXT("bScream"), false);
		}
	}
}
