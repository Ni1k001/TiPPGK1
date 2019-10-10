// Fill out your copyright notice in the Description page of Project Settings.

#include "HexUserWidget.h"

void UHexUserWidget::SetOwningActor(AActor* NewOwner)
{
	if (OwningActor == NewOwner)
	{
		return;
	}

	OwningActor = NewOwner;

	OnOwningActorChanged.Broadcast(NewOwner);
}