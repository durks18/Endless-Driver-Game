// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessDriverGameModeBase.h"
#include "FloorTiles.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

void AEndlessDriverGameModeBase::AddCoin()
{
	TotalCoins += 1;

	UE_LOG(LogTemp, Warning, TEXT("totalCoins: %d"), TotalCoins);
}

void AEndlessDriverGameModeBase::BeginPlay()
{
	CreateInitialFloorTiles(); 
}

void AEndlessDriverGameModeBase::CreateInitialFloorTiles()
{
	AFloorTiles* Tile = AddFloorTiles(false);

	if (Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}

	//for (float val : LaneSwitchValues)
	//{
		//UE_LOG(LogTemp, Warning, TEXT("LANE VALUE: %F"), val);
	//}

	AddFloorTiles(false);
	AddFloorTiles(false);

	for (int i = 0; i < NuminitialFloorTiles; i++)
	{
		AddFloorTiles(true);
	}
}

AFloorTiles* AEndlessDriverGameModeBase::AddFloorTiles(const bool bSpawnItems)
{
	UWorld* World = GetWorld(); 

	if (World)
	{
		AFloorTiles* Tile = World->SpawnActor<AFloorTiles>(FloorTilesClass, NextSpawnPoint);

		if (Tile)
		{

			if (bSpawnItems)
			{
				Tile->SpawnItems();
			}

			NextSpawnPoint = Tile->GetAttachTransform();
		}

		return Tile;
	}

	return nullptr;
}
