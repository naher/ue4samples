// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERIESCPP_API ASpawnVolume : public AActor
{
    GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    ASpawnVolume();

    // Sets default values for this actor's properties
    ASpawnVolume(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(VisibleInstanceOnly, Category = "Spawning")
    class UBoxComponent* WhereToSpawn;

    /* the pickup to spawn */
    UPROPERTY(EditAnywhere, Category = "Spawning")
        TSubclassOf<class APickup> WhatToSpawn;

    /*minimum spawn delay*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
        float SpawnDelayRangeLow;

    /*Maximum spawn delay*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
        float SpawnDelayRangeHigh;

    UFUNCTION(BlueprintPure, Category = "Spawning")
        FVector GetRandomPointInVolume();



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
    UFUNCTION(BlueprintCallable, Category = "Spawning")
        void EnableSpawning();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
        void DisableSpawning();

private:

    /*whether or not spawning is enabled*/
    bool bSpawningEnabled;

    /*calculates spawn delay*/
    float GetRandomSpawnDelay();


    /*the current spawn delay*/
    float SpawnDelay;

    /*handles the spawning of a pickup*/
    void SpawnPickup();

    /*the timer for when to spawn a pickup*/
    float SpawnTime;
};
