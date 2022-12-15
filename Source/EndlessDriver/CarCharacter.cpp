// Fill out your copyright notice in the Description page of Project Settings.


#include "CarCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EndlessDriverGameModeBase.h"
#include "GameFramework/PlayerStart.h"



// Sets default values
ACarCharacter::ACarCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->TargetArmLength = 350.0f;
	CameraArm->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);


}

// Called when the game starts or when spawned
void ACarCharacter::BeginPlay()
{
	Super::BeginPlay();

	DriveGameMode = Cast<AEndlessDriverGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(DriveGameMode);

	//PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
	
}

void ACarCharacter::AddCoin()
{
	DriveGameMode->AddCoin();
}

// Called every frame
void ACarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator  ControlRot = GetControlRotation();
	ControlRot.Roll = 0.f;
	ControlRot.Pitch = 0.f;

	AddMovementInput(ControlRot.Vector());

}


// Called to bind functionality to input
void ACarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACarCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACarCharacter::StopJumping);

	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ACarCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ACarCharacter::MoveRight);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ACarCharacter::MoveDown);

}

void ACarCharacter::ChangeLaneUpdate(float Value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(DriveGameMode->LaneSwitchValues[CurrentLane],DriveGameMode->LaneSwitchValues[NextLane], Value);
	SetActorLocation(Location);

}

void ACarCharacter::ChangeLaneFinsihed()
{
	CurrentLane = NextLane;
}

void ACarCharacter::Death()
{
	if (!bIsDead)
	{
		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();

		if (World)
		{
			bIsDead = true;
			DisableInput(nullptr);

			if (DeathParticleSystem)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, Location);
			}

			if (DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}

			GetMesh()->SetVisibility(false);

			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ACarCharacter::OnDeath, 1.f);
		}
	}
}

void ACarCharacter::OnDeath()
{
	bIsDead = false;

	if (RestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimerHandle);
	}

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("RestartLevel"));
}

void ACarCharacter::MoveLeft()
{
	NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
}

void ACarCharacter::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane +1, 0, 2);
	ChangeLane();
}

void ACarCharacter::MoveDown()
{
	UE_LOG(LogTemp, Warning, TEXT("Move down was pressed"));
}
