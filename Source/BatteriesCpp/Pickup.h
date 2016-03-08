// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERIESCPP_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

    // Sets default values for this actor's properties
    APickup(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    //true when it is able to be picked up
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
        bool bIsActive;

    //collision sphere primitive to use as root component
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pickup")

    class USphereComponent* BaseCollisionComponent;


    //static mesh of our pickup
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pickup")

    class UStaticMeshComponent* PickupMesh;


    //function to call when the pickup is collected
    UFUNCTION(BlueprintNativeEvent)
        void OnPickedUp();
	
};
