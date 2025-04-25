// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CardActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateCombinations.h"
#include "CardSpawner.generated.h"

UCLASS()
class GWENT_API ACardSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to spawn a singular card
	UFUNCTION(BlueprintCallable, Category = "Card Spawner")
	ACardActor* SpawnCard(UCard* CardToSpawn, FVector SpawnLoc, FRotator SpawnRot);

	// Define the delegate type
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCardSpawned, UCard*, Card, ACardActor*, CardActor);

	// Event Dispatcher to call when a card is spawned
	UPROPERTY(BlueprintAssignable, Category = "Card Spawner")
	FOnCardSpawned OnCardSpawned;

	// Function to spawn all cards in a given row
	UFUNCTION(BlueprintCallable, Category = "Card Spawner")
	TArray<ACardActor*> SpawnRow(ECardFaction faction, ECardRow row);

	// Function to get all cards in a given faction
	UFUNCTION(BlueprintCallable, Category = "Card Spawner")
	TArray<UCard*> GetCardsInFaction(ECardFaction faction);

	// Function to load all cards in the game
	UFUNCTION(BlueprintCallable, Category = "Card Spawner")
	TArray<UCard*> LoadAllCards();

	// The card actor class to spawn
	UPROPERTY(EditAnywhere, Category = "Card Spawner")
	TSubclassOf<class ACardActor> CardActorClass;

	// Member variable to store all cards in the game
	UPROPERTY(BlueprintReadOnly, Category = "Card Spawner")
	TArray<UCard*> LoadedCards;
private:

	// Member variables to store row X values
	float playerHandX = 280.0f;
	float playerFleetX = 170.0f;
	float playerInfantryX = 60.0f;
	float playerDeckY = -500.0f;
	float playerDiscardY = -400.0f;
	float playerInPlayY = -270.0f;
	// Opponent rows can be inverse of player rows
	float opponentHandX = -playerHandX;
	float opponentFleetX = -playerFleetX;
	float opponentInfantryX = -playerInfantryX;
	float opponentDeckY = playerDeckY;
	float opponentDiscardY = -playerDiscardY;
};
