// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HexWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class TIPPGK1_API UHexWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UHexWidgetComponent();
	
	virtual void InitWidget() override;
};
