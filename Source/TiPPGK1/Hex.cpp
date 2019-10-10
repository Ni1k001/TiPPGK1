// Fill out your copyright notice in the Description page of Project Settings.

#include "Hex.h"
#include "ConstructorHelpers.h"

// Sets default values
AHex::AHex(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/hex.hex'"));
	UStaticMesh* Asset = Mesh.Object;
	

	HexMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexMesh"));
	HexMesh->SetStaticMesh(Asset);
	HexMesh->SetSimulatePhysics(false);
	HexMesh->SetupAttachment(RootComponent);

	Height = 300.f;
	Width = 100*sqrt(3);

	SelectionType = ESelectionType::ENotSelected;

	WidgetComponent = CreateDefaultSubobject<UHexWidgetComponent>(TEXT("Widget"));

	ConstructorHelpers::FClassFinder<UHexUserWidget> WidgetClassFinder(TEXT("/Game/HexWidget"));
	TSubclassOf<class UHexUserWidget> WidgetClass = WidgetClassFinder.Class;

	Widget = CreateWidget<UHexUserWidget>(GetWorld(), WidgetClass);

	WidgetComponent->AttachTo(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetWidgetClass(WidgetClass);
	WidgetComponent->SetVisibility(true);
	WidgetComponent->SetWidget(Widget);

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/BaseMaterial.BaseMaterial'"));
	if (FoundMaterial.Succeeded())
		StoredMaterial = FoundMaterial.Object;

	DefaultMat = UMaterialInstanceDynamic::Create(StoredMaterial, HexMesh);
	DefaultMat->SetVectorParameterValue("Color", FLinearColor(0.f, 0.5f, 0.f));

	SelectedMat = UMaterialInstanceDynamic::Create(FoundMaterial.Object, HexMesh);
	SelectedMat->SetVectorParameterValue("Color", FLinearColor(0.5f, 0.f, 0.f));

	NeighbourMat = UMaterialInstanceDynamic::Create(FoundMaterial.Object, HexMesh);
	NeighbourMat->SetVectorParameterValue("Color", FLinearColor(0.f, 0.f, 0.5f));
	
	
	HexMesh->SetMaterial(0, DefaultMat);
}

// Called when the game starts or when spawned
void AHex::BeginPlay()
{
	Super::BeginPlay();
	
	WidgetComponent->RegisterComponent();
}

// Called every frame
void AHex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHex::SetCoordX(int X) {	CoordX = X;	}

void AHex::SetCoordY(int Y) {	CoordY = Y;	}

int AHex::GetCoordX() {	return CoordX;	}

int AHex::GetCoordY() {	return CoordY;	}

float AHex::GetHeight() {	return Height;	}

float AHex::GetWidth() { return Width; }

void AHex::OnSelected(ESelectionType::SelectionType Selection)
{
	if (Selection == ESelectionType::ESelected)
	{
		SetSelectionType(Selection);
		HexMesh->SetMaterial(0, SelectedMat);
	}
	else if (Selection == ESelectionType::ENeighbour)
	{
		SetSelectionType(Selection);
		HexMesh->SetMaterial(0, NeighbourMat);
	}
	else
	{
		SetSelectionType(Selection);
		HexMesh->SetMaterial(0, DefaultMat);
	}
}

void AHex::SetSelectionType(ESelectionType::SelectionType Type)
{
	SelectionType = Type;
}

ESelectionType::SelectionType AHex::GetSelectionType()
{
	return SelectionType;
}

UHexWidgetComponent* AHex::GetWidgetComponent()
{
	return WidgetComponent;
}