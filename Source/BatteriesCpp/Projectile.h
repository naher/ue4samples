// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTERIESCPP_API AProjectile : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
        float fDamageAmount;

    /** StaticMeshComponent to represent the pickup in the level */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
        TSubobjectPtr<UStaticMeshComponent> ProjectileMesh;

    /** Projectile movement component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
        UProjectileMovementComponent* ProjectileMovement;

    /** called when projectile hits something */
    UFUNCTION()
        void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    // Sets default values for this actor's properties
    AProjectile();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    /** inits velocity of the projectile in the shoot direction */
    void InitVelocity(const FVector& ShootDirection);

};
