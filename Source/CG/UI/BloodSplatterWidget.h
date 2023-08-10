// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "BloodSplatterWidget.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UBloodSplatterWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	// Function to play first blood splatter HUD animation when attacking.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayBloodSplatterAnimation1();

	// Function to play second blood splatter HUD animation when attacking.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayBloodSplatterAnimation2();

	// Function to play third blood splatter HUD animation when attacking.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayBloodSplatterAnimation3();

	// Function to play fourth blood splatter HUD animation when attacking.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayBloodSplatterAnimation4();
	
};
