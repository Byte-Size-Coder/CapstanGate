// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "UI/EricHUD.h"
#include "CGGameMode.h"


ACGGameMode::ACGGameMode()
	:Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Blueprints/BP_Eric"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEricHUD::StaticClass();
}

