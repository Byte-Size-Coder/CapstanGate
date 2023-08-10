// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "NotifyBloodSplatter.h"




void UNotifyBloodSplatter::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	// Get reference to the player and call the ShowBloodSplatterWidget function.
	AEric* Player = Cast<AEric>(MeshComp->GetOwner());
	if (Player)
	{
		Player->ShowBloodSplatterWidget();
	}
}