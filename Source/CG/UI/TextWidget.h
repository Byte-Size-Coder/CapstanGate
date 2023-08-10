// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateCore.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "TextWidget.generated.h"

/**
 * 
 */
UCLASS()
class CG_API UTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** Reference to the takedown text **/
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetTakeDownText() const;

	/** Reference to KeyCardA Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetTakeDownImageController() const;

	/** Reference to KeyCardA Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetTakeDownImageKeyboard() const;

	/** Reference to the Interact text **/
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetInteractText() const;

	/** Reference to KeyCardA Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetInteractImageController() const;

	/** Reference to KeyCardA Image **/
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetInteractImageKeyboard() const;

};
