// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NotifyDeathFade.h"




void UNotifyDeathFade::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// Get Reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(MeshComp->GetOwner());
	if (Enemy)
	{
		// Get reference of player through the enemy's blackboard variable and call the ShowDeathWidget function.
		if (Enemy->GetController())
		{
			AEnemyController* EnemyController = Cast<AEnemyController>(Enemy->GetController());

			AEric* Player = Cast<AEric>(EnemyController->BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TEXT("Player")));

			Player->ShowDeathWidget();
		}
	}
}