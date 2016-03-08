// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BatteriesCpp.h"
#include "BatteriesCppGameMode.h"
#include "BatteriesCppCharacter.h"

#include "TutorialCodeHUD.h"

ABatteriesCppGameMode::ABatteriesCppGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    HUDClass = ATutorialCodeHUD::StaticClass();

    DecayRate = 0.13f;
}




void ABatteriesCppGameMode::Tick(float DeltaSeconds)
{
    ABatteriesCppCharacter* MyCharacter = Cast<ABatteriesCppCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    //if the character still has power
    if (MyCharacter->PowerLevel > 0.05)
    {
        //decrease the character's power
        MyCharacter->PowerLevel = FMath::FInterpTo(MyCharacter->PowerLevel, 0.f, DeltaSeconds*DecayRate, 1.f);
    }

    else
    {
        SetCurrentState(EPickupBatteryPlayState::EGameOver);

    }
}

void ABatteriesCppGameMode::SetCurrentState(EPickupBatteryPlayState NewState)
{
    CurrentState = NewState;
    HandleNewState(NewState);
}

void ABatteriesCppGameMode::HandleNewState(EPickupBatteryPlayState NewState)
{
    switch (NewState)
    {
    case EPickupBatteryPlayState::EPlaying:
    {
                                              for (ASpawnVolume* Volume : SpawnVolumeActors)
                                              {
                                                  Volume->EnableSpawning();
                                              }
    }
        break;
        // if the game is over the spawn volumes should deactivate
    case EPickupBatteryPlayState::EGameOver:
    {
                                               for (ASpawnVolume* Volume : SpawnVolumeActors)
                                               {
                                                   Volume->DisableSpawning();
                                               }
                                               APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

                                               PlayerController->SetCinematicMode(true, true, true);
    }
        break;
    case EPickupBatteryPlayState::EUnknown:
        break;
    default:
        break;
    }
}

void ABatteriesCppGameMode::BeginPlay()
{
    Super::BeginPlay();

    /*find all volume actors*/

    TArray<AActor*> FoundActors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

    for (auto Actor : FoundActors)
    {
        ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
        if (SpawnVolumeActor)
        {
            SpawnVolumeActors.Add(SpawnVolumeActor);
        }
    }
    SetCurrentState(EPickupBatteryPlayState::EPlaying);


}