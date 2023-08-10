// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CG.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creates a root component to the actor.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Creates a mesh and attaches it to the root component.
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
	Mesh->CastShadow = false;
}


