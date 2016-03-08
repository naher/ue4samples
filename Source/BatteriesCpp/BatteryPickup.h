// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERIESCPP_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
    ABatteryPickup(const FObjectInitializer& ObjectInitializer);

    //Sets the amount of power the battery gives to the player
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
        float PowerLevel;


    //override the OnPickedUp function because this is BlueprintNativeEvent
    virtual void OnPickedUp_Implementation() override;
	
};
