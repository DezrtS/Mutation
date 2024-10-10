// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapTileCollection.h"
#include "GameFramework/Actor.h"
#include "MapTile.generated.h"

UCLASS()
class MUTATION_API AMapTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FMapTileCollection* ParentCollection;
	FIntPoint Position;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
