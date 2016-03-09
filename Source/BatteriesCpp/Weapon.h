// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

enum PositionType {
    hip = 1, ironsight = 2, both = 3
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPositionType : uint8
{
    VE_HIP 	UMETA(DisplayName = "Hip"),
    VE_IRONSIGHTS 	UMETA(DisplayName = "Ironsight"),
    VE_BOTH	UMETA(DisplayName = "Both")
};

UCLASS()
class BATTERIESCPP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:

    /** Gun muzzle's offset from the camera location */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
    FVector MuzzleOffset;

    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AProjectile> ProjectileClass;

    /** true when the pickup is able to be pickedup */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
    bool bIsPickupActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
    uint8 bAmmo;

    // true -> hip weapon -- false -> ironsights weapon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
    EPositionType bHip;

    // true -> rifle fire, false -> shotgun
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
    bool bMultiFire;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
    float BaseLookUpRate;

    /** simple collision primitive to use as the root component */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
    TSubobjectPtr<USphereComponent> BaseCollisionComponent;

    /** StaticMeshComponent to represent the pickup in the level */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
    TSubobjectPtr<USkeletalMeshComponent> WeaponMesh;

    /** function to call when the pickup is collected*/
    UFUNCTION(BlueprintNativeEvent)
    void OnPickedUp(ABatteriesCppCharacter * ACharacter);

    UFUNCTION(BlueprintCallable, Category = Weapon)
    bool CanFire();

    /** function to call when the pickup is collected*/
    UFUNCTION(BlueprintNativeEvent)
    void OnFire();
	
};
