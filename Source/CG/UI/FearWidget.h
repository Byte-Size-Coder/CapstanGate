// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "FearWidget.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UFearWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Function to Show Both fear textures.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowFearWidgetAnimation();

	// Function to show fear texture when seen.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowFearWidgetAnimation2();

	// Function to hide fear texture when no enemies are alerted.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHideFearWidgetAnimation();
	
	// Function to hide fear texture when no enemies see the player.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHideFearWidgetAnimation2();
	
};
