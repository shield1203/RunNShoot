// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActor.h"
#include "Run_N_Shoot1.h"

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_targetOn = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(50.0f);
	RootComponent = CollisionComponent;

	DynamicMaterialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DynamicMaterialMesh"));
	DynamicMaterialMesh->CreateDynamicMaterialInstance(0);
	DynamicMaterialMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetActor::TargetOff()
{
	m_targetOn = false;
	
	FVector ChangeColor = FVector(256.f, 0.f, 0.f);
	DynamicMaterialMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), ChangeColor);
}