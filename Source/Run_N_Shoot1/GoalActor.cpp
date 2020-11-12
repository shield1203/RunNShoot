// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "Run_N_Shoot1.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(50.0f);
	RootComponent = CollisionComponent;

	DynamicMaterialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DynamicMaterialMesh"));
	DynamicMaterialMesh->CreateDynamicMaterialInstance(0);
	DynamicMaterialMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float time = GetGameTimeSinceCreation();

	FVector p = GetActorLocation();
	p.Z += sin(time);

	SetActorLocation(p);
}
