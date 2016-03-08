// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteriesCpp.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Sets default values
APickup::APickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //pickup is valid when it is created
    bIsActive = true;

    //create root sphere component that is collision
    BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

    //Set sphere component as root

    RootComponent = BaseCollisionComponent;

    //create static mesh component
    PickupMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

    //Turn physics on for static mesh
    PickupMesh->SetSimulatePhysics(true);

    //Attach the StaticMeshComponent to the root component
    PickupMesh->AttachTo(RootComponent);


}

void APickup::OnPickedUp_Implementation()
{
    //There is no default behavior for a Pickup
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

