// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDown.h"
#include "Run_N_Shoot1.h"

// Sets default values
ACountDown::ACountDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	m_countText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountDown"));
	m_countText->SetHorizontalAlignment(EHTA_Center);
	m_countText->SetWorldSize(150.0f);

	RootComponent = m_countText;

	m_second = 0;
	m_count = 3;
}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();

	UpdateCountDownText();

	GetWorldTimerManager().SetTimer(m_timerHadle, this, &ACountDown::UpdateTimer, 1.0f, true);
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountDown::UpdateCountDownText()
{
	m_count--;

	if (m_count > 0 )
	{
		m_countText->SetText(FString::FromInt(m_count));
	}
	else if (m_count > -3)
	{
		m_countText->SetText(TEXT("GO"));
	}
	else
	{
		m_countText->SetText(TEXT(" "));
	}
}

void ACountDown::UpdateTimer()
{
	UpdateCountDownText();

	if (m_count < 0)
	{
		m_second++;
	}
}

void ACountDown::FinishTimer()
{
	GetWorldTimerManager().ClearTimer(m_timerHadle);
}

int32 ACountDown::GetCountDownActorMinute()
{
	return m_second / 60;
}

int32 ACountDown::GetCountDownActorSecond()
{
	return m_second % 60;
}