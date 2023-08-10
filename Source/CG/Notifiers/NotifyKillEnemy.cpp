// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Player/Eric.h"
#include "NotifyKillEnemy.h"


void UNotifyKillEnemy::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// Get reference to player and call the KillEnemy function.
	AEric* Player = Cast<AEric>(MeshComp->GetOwner());
	
	if (Player)
	{
		Player->KillEnemy();
	}
}

