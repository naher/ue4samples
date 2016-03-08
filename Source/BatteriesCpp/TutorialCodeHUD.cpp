// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteriesCpp.h"
#include "TutorialCodeHUD.h"

#include "BatteriesCppCharacter.h"
#include "BatteriesCppGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/Canvas.h"
#include "Engine/Font.h"


ATutorialCodeHUD::ATutorialCodeHUD(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UFont> HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
    HUDFont = HUDFontOb.Object;
}


void ATutorialCodeHUD::DrawHUD()
{
    FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

    Super::DrawHUD();

    ABatteriesCppCharacter *MyCharacter = Cast<ABatteriesCppCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

    FString PowerLevelString = FString::Printf(TEXT("%10.1f"), MyCharacter ? FMath::Abs(MyCharacter->PowerLevel) : 0);

    DrawText(PowerLevelString, FColor::White, 50, 50, HUDFont);

    ABatteriesCppGameMode *MyGameMode = Cast<ABatteriesCppGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode->GetCurrentState() == EPickupBatteryPlayState::EGameOver)
    {
        FVector2D GameOverSize;
        GetTextSize(TEXT("GAME OVER"), GameOverSize.X, GameOverSize.Y, HUDFont);

        DrawText(TEXT("GAME OVER"), FColor::White, (ScreenDimensions.X - GameOverSize.X) / 2.0f, (ScreenDimensions.X - GameOverSize.X) / 2.0f, HUDFont);
    }

}