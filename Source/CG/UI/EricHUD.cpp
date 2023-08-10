// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "EricHUD.h"
#include "Player/Eric.h"


AEricHUD::AEricHUD()
{
	// Find Widget classes.
	static ConstructorHelpers::FClassFinder<UTextWidget> TextWidgetAsset(TEXT("/Game/UI/BP_TextWidget"));
	TextWidgetClass = TextWidgetAsset.Class;

	static ConstructorHelpers::FClassFinder<UIconWidget> IconWidgetAsset(TEXT("/Game/UI/BP_IconWidget"));
	IconWidgetClass = IconWidgetAsset.Class;

	static ConstructorHelpers::FClassFinder<UFearWidget> FearWidgetAsset(TEXT("/Game/UI/BP_FearWidget"));
	FearWidgetClass = FearWidgetAsset.Class;

	static ConstructorHelpers::FClassFinder<UBloodSplatterWidget> BloodSplatterWidgetAsset(TEXT("/Game/UI/BP_BloodSplatterWidget"));
	BloodSplatterWidgetClass = BloodSplatterWidgetAsset.Class;

	static ConstructorHelpers::FClassFinder<UDeathWidget> DeathWidgetAsset(TEXT("/Game/UI/BP_DeathWidget"));
	DeathWidgetClass = DeathWidgetAsset.Class;

	// Initial set of variables upon creation.
	bDo = false;

	bAlertDo = false;

	bDisableHud = false;

	bSeenDo = false; 
	

}

void AEricHUD::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Text Widget Setup
	TextWidget = CreateWidget<UTextWidget>(GetOwningPlayerController(), TextWidgetClass);
	TextWidget->GetInteractText()->SetVisibility(ESlateVisibility::Hidden);
	TextWidget->GetInteractText()->SetText(FText::FromString("Interact"));
	TextWidget->GetInteractImageController()->SetOpacity(0.0f);
	TextWidget->GetInteractImageKeyboard()->SetOpacity(0.0f);
	TextWidget->GetTakeDownText()->SetVisibility(ESlateVisibility::Hidden);
	TextWidget->GetTakeDownText()->SetText(FText::FromString("Takedown"));
	TextWidget->GetTakeDownImageController()->SetOpacity(0.0f);
	TextWidget->GetTakeDownImageKeyboard()->SetOpacity(0.0f);
	TextWidget->AddToViewport();

	//Icon Widget Setup
	IconWidget = CreateWidget<UIconWidget>(GetOwningPlayerController(), IconWidgetClass);
	IconWidget->GetKeyCardAImage()->SetOpacity(0.2f);
	IconWidget->GetKeyCardBImage()->SetOpacity(0.2f);
	IconWidget->GetScrewdriverImage()->SetOpacity(0.2f);
	IconWidget->GetKnifeImage()->SetOpacity(0.2f);
	IconWidget->GetRemoteImage()->SetOpacity(0.2f);
	IconWidget->AddToViewport();

	//Fear Widget Setup
	FearWidget = CreateWidget<UFearWidget>(GetOwningPlayerController(), FearWidgetClass);
	FearWidget->AddToViewport();

	
	//Blood Splatter Widget Setup
	BloodSplatterWidget = CreateWidget<UBloodSplatterWidget>(GetOwningPlayerController(), BloodSplatterWidgetClass);
	BloodSplatterWidget->AddToViewport();
	
	//Death Widget Setup
	DeathWidget = CreateWidget<UDeathWidget>(GetOwningPlayerController(), DeathWidgetClass);
	DeathWidget->AddToViewport();
}


void AEricHUD::DrawHUD()
{
	Super::DrawHUD();
		
}

//////////////////////////////////////////////Functions to show and Hide Widgets////////////////////////////////////////////

void AEricHUD::ShowFearWidget()
{
	if (!FearWidget->IsPlayingAnimation() && !bDisableHud)
	{
		FearWidget->PlayShowFearWidgetAnimation();
		bAlertDo = true;
		bSeenDo = true;
	}
}

void AEricHUD::ShowFearWidget2()
{
	if (!FearWidget->IsPlayingAnimation() && !bDisableHud)
	{
		FearWidget->PlayShowFearWidgetAnimation2();
		bSeenDo = true;
	}
}

void AEricHUD::HideFearWidget()
{
	if (!bDisableHud)
	{
		FearWidget->PlayHideFearWidgetAnimation();
		bAlertDo = false;
	}
}

void AEricHUD::HideFearWidget2()
{
	if (!bDisableHud)
	{
		FearWidget->PlayHideFearWidgetAnimation2();
		bSeenDo = false;
	}
}

void AEricHUD::ShowInteractText()
{
	if (!TextWidget->GetInteractText()->IsVisible() && !bDisableHud)
	{
		TextWidget->GetInteractText()->SetVisibility(ESlateVisibility::Visible);
		TextWidget->GetInteractImageController()->SetOpacity(1.0f);
		TextWidget->GetInteractImageKeyboard()->SetOpacity(1.0f);
	}
}

void AEricHUD::HideInteractText()
{
	if (TextWidget->GetInteractText()->IsVisible() && !bDisableHud)
	{
		TextWidget->GetInteractText()->SetVisibility(ESlateVisibility::Hidden);
		TextWidget->GetInteractImageController()->SetOpacity(0.0f);
		TextWidget->GetInteractImageKeyboard()->SetOpacity(0.0f);
	}
	
}

void AEricHUD::ShowTakeDownText()
{
	if (!TextWidget->GetTakeDownText()->IsVisible() && !bDisableHud)
	{
		TextWidget->GetTakeDownText()->SetVisibility(ESlateVisibility::Visible);
		TextWidget->GetTakeDownImageController()->SetOpacity(1.0f);
		TextWidget->GetTakeDownImageKeyboard()->SetOpacity(1.0f);
	}
}

void AEricHUD::HideTakeDownText()
{
	if (TextWidget->GetTakeDownText()->IsVisible() && !bDisableHud)
	{
		TextWidget->GetTakeDownText()->SetVisibility(ESlateVisibility::Hidden);
		TextWidget->GetTakeDownImageController()->SetOpacity(0.0f);
		TextWidget->GetTakeDownImageKeyboard()->SetOpacity(0.0f);
	}	
}

void AEricHUD::DisplayHUD()
{
	if (!IconWidget->IsPlayingAnimation())
	{
		IconWidget->PlayShowHUDAnimation();
	}
}

void AEricHUD::ShowDeathWidget()
{
	DeathWidget->PlayShowDeathAnimation();
}

void AEricHUD::HideDeathWidget()
{
	DeathWidget->PlayHideDeathAnimation();
}

void AEricHUD::ShowBloodSplatterWidget()
{
	// Pick a random number and play specific blood splatter accordingly.
	int32 animNumber = FMath::RandRange(0, 3);

	switch (animNumber)
	{
		default:
			break;
		
		case 0:
			BloodSplatterWidget->PlayBloodSplatterAnimation1();
			UE_LOG(LogTemp, Warning, TEXT("Blood splat 1"));
			break;

		case 1:
			BloodSplatterWidget->PlayBloodSplatterAnimation2();
			UE_LOG(LogTemp, Warning, TEXT("Blood splat 2"));
			break;

		case 2:
			BloodSplatterWidget->PlayBloodSplatterAnimation3();
			UE_LOG(LogTemp, Warning, TEXT("Blood splat 3"));
			break;

		case 3:
			BloodSplatterWidget->PlayBloodSplatterAnimation4();
			UE_LOG(LogTemp, Warning, TEXT("Blood splat 4"));
			break;
	}
}