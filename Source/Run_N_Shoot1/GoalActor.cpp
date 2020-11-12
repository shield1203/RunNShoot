#include "GoalActor.h"
#include "Run_N_Shoot1.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
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
