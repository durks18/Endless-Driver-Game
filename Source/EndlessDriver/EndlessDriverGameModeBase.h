// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessDriverGameModeBase.generated.h"

class AFloorTiles;

/**
 * 
 */
UCLASS()
class ENDLESSDRIVER_API AEndlessDriverGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<AFloorTiles> FloorTilesClass;

	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NuminitialFloorTiles = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		TArray<float> LaneSwitchValues;

	UFUNCTION(BlueprintCallable)
		void CreateInitialFloorTiles();

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		TArray<AFloorTiles*> FloorTiles;

	UFUNCTION(BlueprintCallable)
		AFloorTiles* AddFloorTiles(const bool bSpawnItems);

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		FTransform NextSpawnPoint;

protected:
	virtual void BeginPlay() override;

};
