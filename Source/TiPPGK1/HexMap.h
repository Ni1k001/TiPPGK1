// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hex.h"
#include "GameFramework/Actor.h"
#include "HexMap.generated.h"

UCLASS()
class TIPPGK1_API AHexMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexMap();

	TArray<AHex*> Map;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ResetMap();

	UFUNCTION()
		void FindNeighbours(AHex* Hex);

};
