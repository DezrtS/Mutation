// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapTile.h"
#include "MapTileCollection.h"
#include "Subsystems/WorldSubsystem.h"
#include "GridMapWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MUTATION_API UGridMapWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	FString State;
	int32 Length;
	int32 Width;
	float TileSize;
	UPROPERTY()
	TArray<AMapTile*> MapTiles;
	TArray<FMapTileCollection> MapTileCollections;
	FRandomStream RandomStream;

	void GenerateSquareRoom();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Generation")
	void GenerateGridMap(const int32 Seed = 1, const int32 InLength = 100, const int32 InWidth = 100, const float InTileSize = 100);

	UFUNCTION(BlueprintCallable, Category = "Generation")
	void GenerateRooms(const int32 RoomCount = 5);

	UFUNCTION(BlueprintCallable, Category = "Generation")
	void GenerateHallways();

	bool PlaceMapTile(FMapTileCollection* MapTileCollection, const FIntPoint Position);
	bool PlaceMapTiles(FMapTileCollection* MapTileCollection, TArray<FIntPoint> Positions);
	bool CanPlaceMapTile(const FIntPoint Position);
	bool CanPlaceMapTiles(TArray<FIntPoint> Positions);
	AMapTile* GetMapTile(const FIntPoint Position);
};
