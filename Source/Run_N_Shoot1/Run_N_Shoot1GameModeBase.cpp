// Copyright Epic Games, Inc. All Rights Reserved.


#include "Run_N_Shoot1GameModeBase.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ARun_N_Shoot1GameModeBase::ARun_N_Shoot1GameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ARun_N_Shoot1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(ScoreWidgetClass);
}

void ARun_N_Shoot1GameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }

    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

UUserWidget* ARun_N_Shoot1GameModeBase::GetCurWidget()
{
    return CurrentWidget;
}