// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "HexWidgetComponent.h"
#include "HexUserWidget.h"
#include "Hex.generated.h"

UENUM(BlueprintType)
namespace ESelectionType
{
	enum SelectionType
	{
		ENotSelected			UMETA(DisplayName = "Not Selected"),
		ESelected				UMETA(DisplayName = "Selected"),
		ENeighbour				UMETA(DisplayName = "Neighbour"),
	};
}


UCLASS()
class TIPPGK1_API AHex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHex(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* HexMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UHexWidgetComponent* WidgetComponent;

	UHexUserWidget* Widget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Config)
		int CoordX;

	UPROPERTY(VisibleAnywhere, Category = Config)
		int CoordY;

	float Height;
	float Width;

	UPROPERTY(VisibleAnywhere, Category = Config)
		TEnumAsByte<ESelectionType::SelectionType> SelectionType;
	
	UPROPERTY(VisibleAnywhere, Category = Config)
		UMaterial* StoredMaterial;

	UPROPERTY(VisibleAnywhere, Category = Config)
		UMaterialInstanceDynamic* DefaultMat;
	
	UPROPERTY(VisibleAnywhere, Category = Config)
		UMaterialInstanceDynamic* SelectedMat;
	
	UPROPERTY(VisibleAnywhere, Category = Config)
		UMaterialInstanceDynamic* NeighbourMat;

public:
	UFUNCTION()
		void SetCoordX(int X);
	
	UFUNCTION()
		void SetCoordY(int Y);

	UFUNCTION(BlueprintPure)
		int GetCoordX();

	UFUNCTION(BlueprintPure)
		int GetCoordY();

	UFUNCTION()
		float GetHeight();

	UFUNCTION()
		float GetWidth();

	UFUNCTION()
		void OnSelected(ESelectionType::SelectionType Selection);

	UFUNCTION()
		void SetSelectionType(ESelectionType::SelectionType Type);

	UFUNCTION()
		ESelectionType::SelectionType GetSelectionType();

	UFUNCTION()
		UHexWidgetComponent* GetWidgetComponent();
};
