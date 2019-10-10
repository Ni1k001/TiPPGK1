// Fill out your copyright notice in the Description page of Project Settings.

#include "TiPPGK1GameModeBase.h"
#include "HexPC.h"
#include "HexCharacter.h"

ATiPPGK1GameModeBase::ATiPPGK1GameModeBase()
{
	PlayerControllerClass = AHexPC::StaticClass();
	DefaultPawnClass = AHexCharacter::StaticClass();
}

void ATiPPGK1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}