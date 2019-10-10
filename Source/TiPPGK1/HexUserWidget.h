// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HexUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwningActorChanged, AActor*, NewOwner);

/**
 * 
 */
UCLASS(Abstract)
class TIPPGK1_API UHexUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "ActorWidget")
		AActor* OwningActor;

public:
	UFUNCTION(BlueprintCallable, Category = Config)
		void SetOwningActor(AActor* NewOwner);

	UPROPERTY(BlueprintAssignable, Category = Config)
		FOnOwningActorChanged OnOwningActorChanged;
};
