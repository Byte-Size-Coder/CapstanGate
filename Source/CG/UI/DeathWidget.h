// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DeathWidget.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UDeathWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	// Function to play the death HUD animation
	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowDeathAnimation();

	// Function to remove the Death HUD animation
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHideDeathAnimation();
	
};
