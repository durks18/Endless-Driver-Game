// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "FloorTiles.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class AObstacle;


UCLASS()
class ENDLESSDRIVER_API AFloorTiles : public AActor
{
	GENERATED_BODY()

public:

#pragma region TSubclassOf

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<AObstacle> SmallObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<AObstacle> BigObstacleClass;

#pragma endregion TSubclassOf

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* FloorTriggerBox;

#pragma endregion Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AActor*> ChildActors;

	UFUNCTION(BlueprintCallable)
		void SpawnItems();


	// Sets default values for this actor's properties
	AFloorTiles();

	FORCEINLINE const FTransform& GetAttachTransform() const
	{
		return AttachPoint->GetComponentTransform();
	}

protected:

	UPROPERTY(VisibleInstanceOnly)
		class AEndlessDriverGameModeBase* DriveGameMode;	

	UPROPERTY()
		FTimerHandle DestroyHandle;

	UFUNCTION()
		void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void SpawnLaneItem(UArrowComponent* Lane);


	UFUNCTION(BlueprintCallable)
		void DestroyFloorTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};


