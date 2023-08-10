// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "UI/EricHUD.h"
#include "Player/Eric.h"
#include "Inventory.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UInventory::PickUp(AInteractableItemUtility* Item)
{
	
	AEric* Player = Cast<AEric>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	// Add item to the inventory.
	Inventory.Add(Item->Type);

	// Set the opacity on HUD inventory of specific item to indicate to player you have the item.
	if (Item->Type == SCREWDRIVER)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetScrewdriverImage()->SetOpacity(1.0f);
			Player->ShowScrewDriverTutorial();
		}
		
	}
	else if (Item->Type == REMOTE)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetRemoteImage()->SetOpacity(1.0f);
			Player->ShowRemoteTutorial();
		}
		
	}
	else if (Item->Type == KEYCARD_A)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetKeyCardAImage()->SetOpacity(1.0f);
		}
		
	}
	else if (Item->Type == KEYCARD_B)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetKeyCardBImage()->SetOpacity(1.0f);
		}
	}
	// Destroys the item from the world.
	Item->Destroy();
}

void UInventory::Remove(EInteractableUtilityType Type)
{
	Inventory.Remove(Type);


	// Set the opacity on HUD inventory of specific item to indicate to player you do not have the item anymore.
	if (Type == SCREWDRIVER)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetScrewdriverImage()->SetOpacity(0.2f);
		}

	}
	 if (Type == REMOTE)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetRemoteImage()->SetOpacity(0.2f);
		}

	}
	 if (Type == KEYCARD_A)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetKeyCardAImage()->SetOpacity(0.2f);
		}

	}
	 if (Type == KEYCARD_B)
	{
		AEricHUD* HUD = Cast<AEricHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			HUD->DisplayHUD();
			HUD->IconWidget->GetKeyCardBImage()->SetOpacity(0.2f);
		}
	}
}


bool UInventory::Contains(EInteractableUtilityType Type)
{
	// Go through inventory to check for specific money.
	for (EInteractableUtilityType Item : Inventory)
	{
		if (Item == Type)
		{
			return true;
		}
	}
	// return false if it's not found.
	return false;
}

