// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMapWorldSubsystem.h"

void UGridMapWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // Initialization logic here
    UE_LOG(LogTemp, Log, TEXT("UGridMapManager Initialized"));
}

void UGridMapWorldSubsystem::Deinitialize()
{
    Super::Deinitialize();
    UE_LOG(LogTemp, Log, TEXT("UGridMapManager Deinitialized"));
}

void UGridMapWorldSubsystem::GenerateGridMap(const int32 Seed, const int32 InLength, const int32 InWidth, const float InTileSize)
{
    RandomStream.Initialize(Seed);
    Length = InLength;
    Width = InWidth;
    TileSize = InTileSize;

    const int32 ArraySize = Length * Width;

    MapTiles.SetNum(ArraySize);
    for (int32 i = 0; i < ArraySize; i++)
    {
        MapTiles[i] = nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("UGridMapManager Map Has Been Generated"));
}

void UGridMapWorldSubsystem::GenerateRooms(const int32 RoomCount)
{
    UE_LOG(LogClass, Display, TEXT("Started Generating Rooms"));
    for (int32 i = 0; i < RoomCount; ++i)
    {
        GenerateSquareRoom();
        UE_LOG(LogClass, Display, TEXT("Room Completed"));
    }
}

void UGridMapWorldSubsystem::GenerateSquareRoom()
{
    bool bSuccess = false;
    FMapTileCollection MapTileCollection(EMapTileCollectionType::Room);
    MapTileCollections.Add(MapTileCollection);

    constexpr int32 MaxAttempts = 100; // Max attempts to prevent infinite loop
    int32 Attempts = 0;

    while (!bSuccess && Attempts < MaxAttempts)
    {
        ++Attempts;

        // Randomize room size
        const int32 RoomSize = RandomStream.RandRange(3, 25);

        // Randomize room position ensuring it stays within bounds
        const FIntPoint RoomPosition = FIntPoint(
            RandomStream.RandRange(0, Length - RoomSize),
            RandomStream.RandRange(0, Width - RoomSize)
        );

        TArray<FIntPoint> TilePositions;
        TilePositions.Reserve(RoomSize * RoomSize); // Reserve space for efficiency
        for (int32 x = 0; x < RoomSize; ++x)
        {
            for (int32 y = 0; y < RoomSize; ++y)
            {
                TilePositions.Add(FIntPoint(RoomPosition.X + x, RoomPosition.Y + y));
            }
        }

        bSuccess = PlaceMapTiles(&MapTileCollection, TilePositions);
        if (!bSuccess)
        {
            UE_LOG(LogClass, Warning, TEXT("Failed to generate room, retrying %d/%d"), Attempts, MaxAttempts);
        }
    }

    if (!bSuccess)
    {
        UE_LOG(LogClass, Error, TEXT("Failed to generate room after %d attempts"), MaxAttempts);
    }
    else
    {
        UE_LOG(LogClass, Log, TEXT("Room generated successfully"));
    }
}

void UGridMapWorldSubsystem::GenerateHallways()
{
    UE_LOG(LogClass, Display, TEXT("Generating Hallways"));
    // Hallway generation logic
}

bool UGridMapWorldSubsystem::PlaceMapTile(FMapTileCollection* MapTileCollection, const FIntPoint Position)
{
    if (CanPlaceMapTile(Position))
    {
        const int32 Index = Position.X + Position.Y * Length;
        //AMapTile* Tile = new FTile(MapTileCollection, Position);
        
        //MapTiles[Index] = MapTile;
        //MapTileCollection->Tiles.Add(Tile);
        return true;
    }
    return false;
}

bool UGridMapWorldSubsystem::PlaceMapTiles(FMapTileCollection* MapTileCollection, TArray<FIntPoint> Positions)
{
    if (!CanPlaceMapTiles(Positions))
    {
        return false;
    }
    for (const FIntPoint& Position : Positions)
    {
        PlaceMapTile(MapTileCollection, Position);
    }
    return true;
}

bool UGridMapWorldSubsystem::CanPlaceMapTile(const FIntPoint Position)
{
    if (const int32 Index = Position.X + Position.Y * Length; Index >= 0 && Index < MapTiles.Num())
    {
        return MapTiles[Position.X + Position.Y * Length] == nullptr;
    }
    return false;
}

bool UGridMapWorldSubsystem::CanPlaceMapTiles(TArray<FIntPoint> Positions)
{
    for (const FIntPoint& Position : Positions)
    {
        if (!CanPlaceMapTile(Position))
        {
            return false;
        }
    }
    return true;
}

AMapTile* UGridMapWorldSubsystem::GetMapTile(const FIntPoint Position)
{
    if (const int32 Index = Position.X + Position.Y * Length; Index >= 0 && Index < MapTiles.Num())
    {
        return MapTiles[Position.X + Position.Y * Length];
    }
    return nullptr;
}