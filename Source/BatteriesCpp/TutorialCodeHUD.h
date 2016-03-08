// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TutorialCodeHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTERIESCPP_API ATutorialCodeHUD : public AHUD
{
    //GENERATED_BODY()
    GENERATED_UCLASS_BODY()

public:

    UPROPERTY()
    UFont* HUDFont;
	
    virtual void DrawHUD() OVERRIDE;
	
};
