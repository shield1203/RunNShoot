// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

UCLASS()
class RUN_N_SHOOT1_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeaponProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION(BlueprintCallable, Category = "Targets")
	void TargetCollisionCheck();
};
