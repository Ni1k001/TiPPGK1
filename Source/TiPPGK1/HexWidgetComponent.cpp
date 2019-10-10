// Fill out your copyright notice in the Description page of Project Settings.

#include "HexWidgetComponent.h"
#include "HexUserWidget.h"

UHexWidgetComponent::UHexWidgetComponent()
{
	SetDrawAtDesiredSize(true);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UHexWidgetComponent::InitWidget()
{
	Super::InitWidget();

	if (Widget)
	{
#if !UE_BUILD_SHIPPING
		if (!Widget->IsA(UHexUserWidget::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("WidgetClass for %s does not derive from SActorWidget"), *GetNameSafe(GetOwner()));
		}
#endif
		UHexUserWidget* WidgetInst = Cast<UHexUserWidget>(Widget);
		if (WidgetInst)
		{
			WidgetInst->SetOwningActor(GetOwner());
		}
	}
}