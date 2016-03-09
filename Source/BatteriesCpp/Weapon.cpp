// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteriesCpp.h"

#include "BatteriesCppCharacter.h"
#include "Weapon.h"
#include "Projectile.h"


// Sets default values
AWeapon::AWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    bIsPickupActive = true;

    bAmmo = 0;
    bMultiFire = false;
    bHip = EPositionType::VE_BOTH;

    // create the root spherecomponent to handle the pickup´s collision
    BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseSphereComponent"));

    // set the spherecomponent as the root component
    RootComponent = BaseCollisionComponent;

    // create the static mesh component
    WeaponMesh = CreateAbstractDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

    // turn phisics on
    WeaponMesh->SetSimulatePhysics(true);

    // attache the static mesh component to the root component
    WeaponMesh->AttachTo(RootComponent);

    MuzzleOffset = FVector(100, 0, 0);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


bool AWeapon::CanFire()
{
    return true;
    // return bAmmo > 0;
}


void AWeapon::OnPickedUp_Implementation(ABatteriesCppCharacter * ACharacter)
{
    /*
    ACharacter->Weapon = this;
    FName HandR01SocketName("handRSocket01");
    WeaponMesh->SetSimulatePhysics(false);
    WeaponMesh->AttachTo(ACharacter->GetMesh(), HandR01SocketName, EAttachLocation::SnapToTarget);
    */
}

void AWeapon::OnFire_Implementation()
{
    // try and fire a projectile
    if (ProjectileClass != NULL)
    {
        // Get the camera transform
        FVector CameraLoc;
        FRotator CameraRot;
        GetActorEyesViewPoint(CameraLoc, CameraRot);
        // MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
        FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRot;
        MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
        UWorld* const World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            // spawn the projectile at the muzzle
            AProjectile* const Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // find launch direction
                FVector const LaunchDir = MuzzleRotation.Vector();
                Projectile->InitVelocity(LaunchDir);
            }
        }
    }
}


