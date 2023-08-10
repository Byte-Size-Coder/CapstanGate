// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "NotifyScream.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UNotifyScream : public UAnimNotify
{
	GENERATED_BODY()
	
	
public:
	// Notiy Function
	virtual void Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);
	
};
