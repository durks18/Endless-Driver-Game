// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CarCharacter.generated.h"

UCLASS()
class ENDLESSDRIVER_API ACarCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly)
		class AEndlessDriverGameModeBase* DriveGameMode;


public:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 CurrentLane = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 NextLane = 0;

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
		void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneUpdate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneFinsihed();


	// Sets default values for this character's properties
	ACarCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void MoveLeft();

	UFUNCTION()
		void MoveRight();

	UFUNCTION()
		void MoveDown();

	UPROPERTY()
		class APlayerStart* PlayerStart;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
