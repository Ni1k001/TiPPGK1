// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCharacter.h"
#include "Hex.h"
#include "HexMap.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"

// Sets default values
AHexCharacter::AHexCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->GravityScale = 0.f;

	//OnClicked.AddDynamic(this, &AHexCharacter::OnSelected);
}

// Called when the game starts or when spawned
void AHexCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHexCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Click", IE_Pressed, this, &AHexCharacter::OnSelected);

	InputComponent->BindAxis("MoveUp", this, &AHexCharacter::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AHexCharacter::MoveRight);
}


void AHexCharacter::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}
}

void AHexCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
	}
}

void AHexCharacter::OnSelected()
{
	FHitResult Hit(ForceInit);
	FVector Start = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FVector End = Start + (Forward * 10000.f);
	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start + Forward * 50.f, End, FColor::Green, true, 5.f, false, 4.f);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start + Forward * 50.f, End, ECC_Visibility, CollisionParams))
	{
		if (Hit.bBlockingHit)
		{
			if (Hit.GetActor()->GetClass()->IsChildOf(AHex::StaticClass()))
			{
				AHex* Hex = Cast<AHex>(Hit.GetActor());
				if (Hex)
				{
					AHexMap* HexMap = Cast<AHexMap>(Hex->GetOwner());
					if (HexMap)
					{
						HexMap->ResetMap();

						UE_LOG(LogTemp, Warning, TEXT("Coords: %d %d"), Hex->GetCoordX(), Hex->GetCoordY());

						Hex->OnSelected(ESelectionType::ESelected);

						HexMap->FindNeighbours(Hex);
					}
					else
						UE_LOG(LogTemp, Error, TEXT("HexMap is unable to obtain."));
				}
				else
					UE_LOG(LogTemp, Error, TEXT("Hex is unable to obtain."));
			}
		}
	}
}