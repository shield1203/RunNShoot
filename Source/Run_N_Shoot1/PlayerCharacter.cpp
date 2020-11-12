// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Run_N_Shoot1.h"
#include "WeaponProjectile.h"
#include "TargetActor.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_bDash = false;
	m_bZoom = false;
	m_bFireLeft = false;

	m_score = 0.f;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));
	
	GetCharacterMovement()->JumpZVelocity = 600.f;

	m_cameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCharacterCameraSpringArm"));
	m_cameraSpringArmComponent->SetupAttachment(GetCapsuleComponent());
	m_cameraSpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	m_cameraSpringArmComponent->TargetArmLength = 200.0f;
	m_cameraSpringArmComponent->SocketOffset.Z = 30.0f;
	m_cameraSpringArmComponent->bUsePawnControlRotation = true;

	m_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCharacterCamera"));
	m_cameraComponent->SetupAttachment(m_cameraSpringArmComponent, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Log, TEXT("44"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateScore();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("SideRight", this, &APlayerCharacter::SideRight);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);
	InputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::DashOn);
	InputComponent->BindAction("Dash", IE_Released, this, &APlayerCharacter::DashOff);
	InputComponent->BindAction("Zoom", IE_Pressed, this, &APlayerCharacter::ZoomIn);
	InputComponent->BindAction("Zoom", IE_Released, this, &APlayerCharacter::ZoomOut);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();

	if (m_bDash && AxisValue > 0.0f)
	{
		AxisValue *= 2.5;
	}

	AddMovementInput(Direction, AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	
	if (m_bDash)
	{
		AxisValue *= 2;
	}

	AddMovementInput(Direction, AxisValue);
}

void APlayerCharacter::SideRight(float AxisValue)
{
	if (m_bZoom) return;

	float sideValue = m_cameraSpringArmComponent->SocketOffset.Y;

	if (AxisValue == 0.0f)
	{
		if (sideValue != 0.0f)
		{
			AxisValue = (sideValue < 0.0f) ? 5.0f : -5.0f;
		}
	}
	
	sideValue += AxisValue;

	m_cameraSpringArmComponent->SocketOffset.Y = FMath::Clamp(sideValue, -60.f, 60.f);
	FMath::Clamp(m_cameraSpringArmComponent->SocketOffset.Y, -60.f, 60.f);
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::DashOn()
{
	m_bDash = true;
}

void APlayerCharacter::DashOff()
{
	m_bDash = false;
}

void APlayerCharacter::ZoomIn()
{
	m_bZoom = true;

	m_cameraSpringArmComponent->TargetArmLength = 100.0f;
	m_cameraSpringArmComponent->SocketOffset.Y = 60.0f;
}

void APlayerCharacter::ZoomOut()
{
	m_bZoom = false;

	m_cameraSpringArmComponent->TargetArmLength = 200.0f;
	m_cameraSpringArmComponent->SocketOffset.Y = 0.0f;
}

void APlayerCharacter::Fire()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		if (!m_bFireLeft)
		{
			MuzzleLocation.Y -= 25;
			m_bFireLeft = true;
		}
		else
		{
			MuzzleLocation.Y += 25;
			m_bFireLeft = false;
		}

		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			//SpawnParams.Instigator = Instigator;
			AWeaponProjectile* Projectile = World->SpawnActor<AWeaponProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void APlayerCharacter::UpdateScore()
{
	m_score = 0.f;

	UWorld* world = GetWorld();

	for (const auto& entity : TActorRange<ATargetActor>(world))
	{
		if (!entity->IsTargetOn())
		{
			m_score += 200.f;
		}
	}
}

float APlayerCharacter::GetPlayerScore()
{
	return m_score;
}