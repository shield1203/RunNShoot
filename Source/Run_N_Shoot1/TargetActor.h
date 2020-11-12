// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

UCLASS()
class RUN_N_SHOOT1_API ATargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetActor();

	bool m_targetOn;

	UPROPERTY(VisibleDefaultsOnly, Category = "TargetCollision")
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* DynamicMaterialMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool IsTargetOn() const { return m_targetOn; }

	UFUNCTION()
	void TargetOff();
};
