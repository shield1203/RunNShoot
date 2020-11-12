// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RUN_N_SHOOT1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* m_cameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* m_cameraComponent;

	bool m_bDash;
	bool m_bZoom;
	bool m_bFireLeft;

	// Function
	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void SideRight(float AxisValue);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void DashOn();

	UFUNCTION()
	void DashOff();

	UFUNCTION()
	void ZoomIn();

	UFUNCTION()
	void ZoomOut();

	UFUNCTION()
	void Fire();

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	float m_score;

	void UpdateScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
	float GetPlayerScore();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
