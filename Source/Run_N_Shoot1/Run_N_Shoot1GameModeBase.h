// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Run_N_Shoot1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUN_N_SHOOT1_API ARun_N_Shoot1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARun_N_Shoot1GameModeBase();

	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	class UUserWidget* GetCurWidget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
