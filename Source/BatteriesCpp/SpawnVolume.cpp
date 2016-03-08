// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteriesCpp.h"
#include "SpawnVolume.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Create the simple static mesh to represent the pickup in level
    WhereToSpawn = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));

    // Set the StaticMeshComponent as the root component
    RootComponent = WhereToSpawn;

    //Set the spawn delay range and get the first SpawnDelay
    SpawnDelayRangeLow = 1.f;
    SpawnDelayRangeHigh = 1.f;
    SpawnDelay = GetRandomSpawnDelay();

}



void ASpawnVolume::SpawnPickup()
{
    if (WhatToSpawn != NULL)
    {	//check for a valid world
        UWorld* const World = GetWorld();
        if (World)
        {
            //Set the spawn parameters
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;

            //Get a random location to spawn at
            FVector SpawnLocation = GetRandomPointInVolume();

            FRotator SpawnRotation;
            SpawnRotation.Yaw = FMath::FRand()*360.f;
            SpawnRotation.Pitch = FMath::FRand()*360.f;
            SpawnRotation.Roll = FMath::FRand()*360.f;

            // spawn the pickup
            APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

        }
    }
}


FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector RandomLocation;
    float MinX, MinY, MinZ;
    float MaxX, MaxY, MaxZ;
    FVector Origin;
    FVector BoxExtent;

    //Get the SpawnVolume's origin and box extent

    Origin = WhereToSpawn->Bounds.Origin;
    BoxExtent = WhereToSpawn->Bounds.BoxExtent;

    /*Calculate the min X,Y,Z*/

    MinX = Origin.X - BoxExtent.X / 2.f;
    MinY = Origin.Y - BoxExtent.Y / 2.f;
    MinZ = Origin.Z - BoxExtent.Z / 2.f;

    /*Calculate the max X,Y,Z*/
    MaxX = Origin.X + BoxExtent.X / 2.f;
    MaxY = Origin.Y + BoxExtent.Y / 2.f;
    MaxZ = Origin.Z + BoxExtent.Z / 2.f;

    RandomLocation.X = FMath::FRandRange(MinX, MaxX);
    RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
    RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

    return RandomLocation;
}


float ASpawnVolume::GetRandomSpawnDelay()
{
    return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}


// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
    /*if spawning is not enabled , do nothing*/
    if (!bSpawningEnabled)
    {
        return;
    }

    Super::Tick(DeltaTime);
    //Always add time to our spawn time
    SpawnTime += DeltaTime;
    bool bShouldSpawn = (SpawnTime > SpawnDelay);

    if (bShouldSpawn)
    {
        SpawnPickup();
        //deduct spawn delay from accumulated spawn value

        SpawnTime -= SpawnDelay;

        SpawnDelay = GetRandomSpawnDelay();
    }
}


void ASpawnVolume::EnableSpawning()
{
    bSpawningEnabled = true;
}

void ASpawnVolume::DisableSpawning()
{
    bSpawningEnabled = false;
}
