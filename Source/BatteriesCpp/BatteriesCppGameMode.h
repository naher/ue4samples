// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SpawnVolume.h"
#include "BatteriesCppGameMode.generated.h"


/*enum to store the current state of gameplay*/
enum class EPickupBatteryPlayState : short
{
    EPlaying,
    EGameOver,
    EUnknown
};

UCLASS(minimalapi)
class ABatteriesCppGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteriesCppGameMode(const FObjectInitializer& ObjectInitializer);

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;


    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
        float DecayRate;

    EPickupBatteryPlayState GetCurrentState() const;

    void SetCurrentState(EPickupBatteryPlayState NewState);


    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

    TArray<ASpawnVolume*> SpawnVolumeActors;

    EPickupBatteryPlayState CurrentState;
    void HandleNewState(EPickupBatteryPlayState NewState);


};

FORCEINLINE EPickupBatteryPlayState ABatteriesCppGameMode::GetCurrentState() const
{
    return CurrentState;
}



