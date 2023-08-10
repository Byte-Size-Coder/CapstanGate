// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "Waypoint.generated.h"

/**
 * 
 */
UCLASS()
class CG_API AWaypoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	/** Reference to the next waypoint */
	UPROPERTY(EditInstanceOnly)
	AWaypoint* NextWaypoint;	

	// Bool varable to check if enemy needs to do something (play animation).
	UPROPERTY(EditInstanceOnly)
	bool bDoSomething;

	// Float variable for the wait time of enemy.
	UPROPERTY(EditInstanceOnly)
	float WaitTime;

};
