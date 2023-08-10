// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "NotifyDestroyPlayer.h"


void UNotifyDestroyPlayer::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// Get Reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(MeshComp->GetOwner());
	if (Enemy)
	{
		AEnemyController* EnemyController = Cast<AEnemyController>(Enemy->GetController());

		// Call the KillPlayer function from enemy.
		Enemy->KillPlayer();

		// Reset blackboard variable of player.
		if (EnemyController)
		{
			EnemyController->BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TEXT("Player"), NULL);
		}
	}
}

