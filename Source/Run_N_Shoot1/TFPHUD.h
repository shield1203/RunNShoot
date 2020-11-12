// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TFPHUD.generated.h"

/**
 * 
 */
UCLASS()
class RUN_N_SHOOT1_API ATFPHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
public:
	virtual void DrawHUD() override;
};
