// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProjectile.h"
#include "Run_N_Shoot1.h"
#include "TargetActor.h"

// Sets default values
AWeaponProjectile::AWeaponProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 4000.0f;
	ProjectileMovementComponent->MaxSpeed = 4000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TargetCollisionCheck();
}

void AWeaponProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AWeaponProjectile::TargetCollisionCheck()
{
	TArray<AActor*> CollectedActors;
	CollisionComponent->GetOverlappingActors(CollectedActors);

	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		ATargetActor* const TestTartget = Cast<ATargetActor>(CollectedActors[iCollected]);
		if (TestTartget && TestTartget->IsTargetOn())
		{
			TestTartget->TargetOff();
		}
	}
}