// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "Player/Eric.h"
#include "AI/Enemy.h"
#include "AI/EnemyController.h"
#include "NotifyBloodSplatter.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UNotifyBloodSplatter : public UAnimNotify
{
	GENERATED_BODY()
	
	
public:
	// Notiy Function
	virtual void Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);
	
};
