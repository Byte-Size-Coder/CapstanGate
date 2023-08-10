// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"

#include "UI/TextWidget.h"
#include "UI/FearWidget.h"
#include "UI/IconWidget.h"
#include "UI/DeathWidget.h"
#include "UI/BloodSplatterWidget.h"
#include "EricHUD.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AEricHUD : public AHUD
{
	GENERATED_BODY()

public:
	AEricHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	/** Functions to show and Hide specific HUD Widgets**/
	void ShowInteractText();

	void HideInteractText();

	void ShowTakeDownText();

	void HideTakeDownText();

	void ShowFearWidget();

	void ShowFearWidget2();

	void HideFearWidget();

	void HideFearWidget2();

	void DisplayHUD();

	void HideHUD();

	void ShowDeathWidget();

	void HideDeathWidget();

	void ShowBloodSplatterWidget();

	// Necessary variables to carry out functions.

	bool bDo;

	bool bAlertDo;

	bool bSeenDo;

	UPROPERTY(BlueprintReadWrite)
	bool bDisableHud;

	FTimerHandle OnTime;

	/** Reference to icon Widget **/
	TSubclassOf<UIconWidget> IconWidgetClass;
	UIconWidget* IconWidget;


private:
	
	/** Reference to text widget **/
	TSubclassOf<UTextWidget> TextWidgetClass;
	UTextWidget* TextWidget;

	/** Reference to death widget **/
	TSubclassOf<UDeathWidget> DeathWidgetClass;
	UDeathWidget* DeathWidget;

	/** Reference to fear widget **/
	TSubclassOf<UFearWidget> FearWidgetClass;
	UFearWidget* FearWidget;

	/** Reference to blood splatter widget **/
	TSubclassOf<UBloodSplatterWidget> BloodSplatterWidgetClass;
	UBloodSplatterWidget* BloodSplatterWidget;

	// Reference to the player
	class AEric * Player;

	UUserWidget * Temp;

	

};
