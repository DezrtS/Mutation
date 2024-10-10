// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EMapTileCollectionType
{
 None,
 Room,
 Hallway
};

/**
 * 
 */
struct MUTATION_API FMapTileCollection
{
 EMapTileCollectionType MapTileCollectionType;
 FIntPoint CollectionOrigin;
 //TArray<AMapTile*> MapTiles;

 explicit FMapTileCollection(const EMapTileCollectionType InMapTileCollectionType): MapTileCollectionType(InMapTileCollectionType), CollectionOrigin(FIntPoint()) {}
 FMapTileCollection(const EMapTileCollectionType InMapTileCollectionType, const FIntPoint InCollectionOrigin) : MapTileCollectionType(InMapTileCollectionType), CollectionOrigin(InCollectionOrigin) {}
};
