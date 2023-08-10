// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BTTLockPlayer.h"


UBTTLockPlayer::UBTTLockPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTLockPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// If there is no world, the execution fails.
	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}


	// Get reference to the player.
	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Get reference to the enemy.
	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("SelfActor")));

	// Get reference to the enemy controller.
	AEnemyController* EnemyC = Cast<AEnemyController>(Enemy->GetController());

	if (Player->bAttacked)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		// Execute the player's LookandLock function and pass in the enemy.
		Player->LookAndLock(Enemy);

		// Call Start Attack function on Enemy to Turn enemy smoothly to face player.
		Enemy->StartAttack(Enemy->GetActorLocation(), Player->GetActorLocation(), 1.0f);

		// Set notification that enemy has killed the player.
		Enemy->SetKilledPlayer(true);

		return EBTNodeResult::Succeeded;
	}

}