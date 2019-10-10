// Fill out your copyright notice in the Description page of Project Settings.

#include "HexMap.h"
#include "Engine.h"

// Sets default values
AHexMap::AHexMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHexMap::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			AHex* Hex = GetWorld()->SpawnActor<AHex>();
			Hex->SetOwner(this);
			Hex->SetCoordX(i);
			Hex->SetCoordY(j * 2);
			Hex->SetActorLocation(FVector(i * Hex->GetWidth(), j * Hex->GetHeight(), 0.f));
			Hex->GetWidgetComponent()->MoveComponent(FVector(i * Hex->GetWidth(), j * Hex->GetHeight(), 10.f), FRotator(90.f, 90.f, 0.f), true);
			Map.Add(Hex);
		}

		for (int j = 0; j < 15; j++)
		{
			AHex* Hex = GetWorld()->SpawnActor<AHex>();
			Hex->SetOwner(this);
			Hex->SetCoordX(i);
			Hex->SetCoordY(j * 2 + 1);
			Hex->SetActorLocation(FVector(i * Hex->GetWidth() + Hex->GetWidth() / 2, j * Hex->GetHeight() + Hex->GetHeight() / 2, 0.f));
			Hex->GetWidgetComponent()->MoveComponent(FVector(i * Hex->GetWidth() + Hex->GetWidth() / 2, j * Hex->GetHeight() + Hex->GetHeight() / 2, 10.f), FRotator(90.f, 90.f, 0.f), true);
			Map.Add(Hex);
		}
	}
}

// Called every frame
void AHexMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexMap::ResetMap()
{
	for (AHex* hex : Map)
	{
		hex->OnSelected(ESelectionType::ENotSelected);
	}
}

void AHexMap::FindNeighbours(AHex* Hex)
{
	int index = Map.Find(Hex);

		if (Hex->GetCoordY() % 2 == 0)
	{
		for (AHex* hex : Map)
		{

			if ((hex->GetCoordX() + 1 == Hex->GetCoordX() && hex->GetCoordY() + 1 == Hex->GetCoordY()) ||
				(hex->GetCoordX() == Hex->GetCoordX() && hex->GetCoordY() + 1 == Hex->GetCoordY()) ||
				(hex->GetCoordX() + 1 == Hex->GetCoordX() && hex->GetCoordY() == Hex->GetCoordY()) ||
				(hex->GetCoordX() - 1 == Hex->GetCoordX() && hex->GetCoordY() == Hex->GetCoordY()) ||
				(hex->GetCoordX() + 1 == Hex->GetCoordX() && hex->GetCoordY() - 1 == Hex->GetCoordY()) ||
				(hex->GetCoordX() == Hex->GetCoordX() && hex->GetCoordY() - 1 == Hex->GetCoordY()))
				hex->OnSelected(ESelectionType::ENeighbour);
		}
	}
	else
	{
		for (AHex* hex : Map)
		{
			if ((hex->GetCoordX() == Hex->GetCoordX() && hex->GetCoordY() + 1 == Hex->GetCoordY()) ||
				(hex->GetCoordX() - 1 == Hex->GetCoordX() && hex->GetCoordY() + 1 == Hex->GetCoordY()) ||
				(hex->GetCoordX() + 1 == Hex->GetCoordX() && hex->GetCoordY() == Hex->GetCoordY()) ||
				(hex->GetCoordX() - 1 == Hex->GetCoordX() && hex->GetCoordY() == Hex->GetCoordY()) ||
				(hex->GetCoordX() == Hex->GetCoordX() && hex->GetCoordY() - 1 == Hex->GetCoordY()) ||
				(hex->GetCoordX() - 1 == Hex->GetCoordX() && hex->GetCoordY() - 1 == Hex->GetCoordY()))
				hex->OnSelected(ESelectionType::ENeighbour);
		}
	}
}