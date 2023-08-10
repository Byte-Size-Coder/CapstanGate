// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateCore.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "IconWidget.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UIconWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:

	/** Reference to KeyCardA Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetKeyCardAImage() const;

	/** Reference to KeyCardB Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetKeyCardBImage() const;

	/** Reference to Knife Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetKnifeImage() const;

	/** Reference to Screwdriver Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetScrewdriverImage() const;

	/** Reference to Remote Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetRemoteImage() const;


	// Function to Show the HUD
	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowHUDAnimation();

	// Function to Hide the HUD
	UFUNCTION(BlueprintImplementableEvent)
	void ReverseShowHUDAnimation();
};
