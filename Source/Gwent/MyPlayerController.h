// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GWENT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this player controller's properties
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnLeftClick();

	UFUNCTION()
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;
	
};
