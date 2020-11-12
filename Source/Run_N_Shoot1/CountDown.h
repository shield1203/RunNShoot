// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "CountDown.generated.h"

UCLASS()
class RUN_N_SHOOT1_API ACountDown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UTextRenderComponent* m_countText;
	int32 m_second;
	int32 m_count;

	FTimerHandle m_timerHadle;

	void UpdateCountDownText();
	void UpdateTimer();
	void FinishTimer();

	UFUNCTION(BlueprintCallable, Category = "CountTime")
	int32 GetCountDownActorMinute();

	UFUNCTION(BlueprintCallable, Category = "CountTime")
	int32 GetCountDownActorSecond();
};
