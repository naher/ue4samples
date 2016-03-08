// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteriesCpp.h"
#include "BatteryPickup.h"


ABatteryPickup::ABatteryPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

    //Base power level of a battery
    PowerLevel = 150.f;

}

void ABatteryPickup::OnPickedUp_Implementation()
{
    Super::OnPickedUp_Implementation();
    Destroy();
}


