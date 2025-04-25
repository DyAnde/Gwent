// Fill out your copyright notice in the Description page of Project Settings.


#include "CardSpawner.h"
#include "CardActor.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/World.h"

// Sets default values
ACardSpawner::ACardSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACardSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* Function to get all cards in a given faction
* 
* @param faction - The faction to filter cards by
* @return An array of cards that belong to the specified faction
*/
TArray<UCard*> ACardSpawner::GetCardsInFaction(ECardFaction faction)
{
	TArray<UCard*> factionCards;
	for (UCard* card : LoadedCards)
	{
		if (card->CardFaction == faction)
		{
			factionCards.Emplace(card);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("FUNC: 'GetCardsInFaction'\tTotal cards loaded: %d"), factionCards.Num());
	return factionCards;
}

/* Function to spawn a card
* 
* @param CardToSpawn - The card to spawn
* @param SpawnLoc - The location to spawn the card (default is (0, 0, 5))
* @param SpawnRot - The rotation to spawn the card (default is (0, 0, 0))
* @return The spawned card actor
*/
ACardActor* ACardSpawner::SpawnCard(UCard* CardToSpawn,
							 FVector SpawnLoc = FVector(0.0f, 0.0f, 5.0f),
							 FRotator SpawnRot = FRotator(0.0f, 0.0f, 0.0f))
{
	if (CardActorClass)
	{
		// Spawn the card actor at the given location and rotation
		FActorSpawnParameters SpawnParams;
		ACardActor* SpawnedCard = GetWorld()->SpawnActor<ACardActor>(CardActorClass, SpawnLoc, SpawnRot, SpawnParams);
		
		// Set the to be spawned card's data
		if (SpawnedCard)
		{
			SpawnedCard->InitializeCard(CardToSpawn);
			UE_LOG(LogTemp, Log, TEXT("Card spawned successfully: %s"), *CardToSpawn->CardName);

			// Add the spawned card into an outliner folder
			SpawnedCard->SetFolderPath(TEXT("SpawnedCards"));

			// Add a tag to the spawned card for easier identification
			SpawnedCard->Tags.Add(FName("SpawnedCard"));

			// Trigger the OnCardSpawned event
			OnCardSpawned.Broadcast(CardToSpawn, SpawnedCard);
			return SpawnedCard;
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn card: %s\n<SpawnedCard> is null"), *CardToSpawn->CardName);
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CardActorClass is not set"));
		return nullptr;
	}
}



/* Function to spawn all cards in a given row
* 
* @param faction - The faction of the cards to spawn
* @param row - The row to spawn the cards in
* @return An array of spawned card actors
*/
TArray<ACardActor*> ACardSpawner::SpawnRow(ECardFaction faction, ECardRow row)
{
	UE_LOG(LogTemp, Log, TEXT("FUNC: 'SpawnRow'\tFaction: %s\tRow: %s"), *UEnum::GetValueAsString(faction), *UEnum::GetValueAsString(row));
	// Get all cards of the faction
	TArray<UCard*> cards = GetCardsInFaction(faction);

	TArray<ACardActor*> spawnedCards;

	FVector InitSpawnLoc = FVector(0.0f, 0.0f, 5.0f);
	//FRotator InitSpawnRot = FRotator(0.0f, 0.0f, 0.0f);

	float spacing = 75.0f;

	// Iterate through the cards and spawn them with the SpawnCard function
	//for (UCard* card : cards)
	for (int32 i = 0; i < cards.Num(); i++)
	{
		UCard* card = cards[i];
		if (card->CardRow == row)
		{
			FVector SpawnLoc = InitSpawnLoc;
			SpawnLoc.Y = playerInPlayY;
			// Deck and Discard rows are ok to have cards stacked on each other
			switch (row)
			{
			case ECardRow::PlayerOneDeck:
				SpawnLoc.Y = playerDeckY;
				break;
			case ECardRow::PlayerTwoDeck:
				SpawnLoc.Y = opponentDeckY;
				break;
			case ECardRow::PlayerOneDiscard:
				SpawnLoc.Y = playerDiscardY;
				break;
			case ECardRow::PlayerTwoDiscard:
				SpawnLoc.Y = opponentDiscardY;
				break;
			default:
				SpawnLoc.Y += i * spacing;
				break;
			}
			/*
			* Pre switch version
			if (row != ECardRow::PlayerOneDeck && row != ECardRow::PlayerOneDiscard
				&& row != ECardRow::PlayerTwoDeck && row != ECardRow::PlayerTwoDiscard)
			{
				SpawnLoc.Y += i * spacing;
			}
			else if (row == ECardRow::PlayerOneDeck)
			{
				SpawnLoc.Y = playerDeckY;
			}
			else if (row == ECardRow::PlayerTwoDeck)
			{
				SpawnLoc.Y = opponentDeckY;
			}
			else if (row == ECardRow::PlayerOneDiscard)
			{
				SpawnLoc.Y = playerDiscardY;
			}
			else if (row == ECardRow::PlayerTwoDiscard)
			{
				SpawnLoc.Y = opponentDiscardY;
			}
			*/

			UE_LOG(LogTemp, Log, TEXT("FUNC: 'SpawnRow'\t'SpawnLoc.Y' set."));
			
			switch (row)
			{
			case ECardRow::PlayerOneInfantry:
				SpawnLoc.X = playerInfantryX;
				break;
			case ECardRow::PlayerTwoInfantry:
				SpawnLoc.X = opponentInfantryX;
				break;
			case ECardRow::PlayerOneFleet:
				SpawnLoc.X = playerFleetX;
				break;
			case ECardRow::PlayerTwoFleet:
				SpawnLoc.X = opponentFleetX;
				break;
			case ECardRow::Hand:
				SpawnLoc.X = playerHandX;
				break;
			case ECardRow::PlayerOneDeck:
				SpawnLoc.X = playerHandX;
				break;
			case ECardRow::PlayerTwoDeck:
				SpawnLoc.X = opponentHandX;
				break;
			case ECardRow::PlayerOneDiscard:
				UE_LOG(LogTemp, Log, TEXT("ROW: 'Discard'\tX value not yet implemented."));
				break;
			case ECardRow::Weather:
				UE_LOG(LogTemp, Log, TEXT("ROW: 'Weather'\tX value not yet implemented."));
				break;
			default:
				break;
			}

			UE_LOG(LogTemp, Log, TEXT("FUNC: 'SpawnRow'\t'SpawnLoc.X' set."));

			spawnedCards.Add(SpawnCard(card, SpawnLoc));
		}
	}
	return spawnedCards;
}

// Function to load all cards in the game
TArray<UCard*> ACardSpawner::LoadAllCards()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	FPrimaryAssetType CardAssetType = TEXT("Card");

	TArray<FPrimaryAssetId> CardIds;
	AssetManager.GetPrimaryAssetIdList(CardAssetType, CardIds);
	UE_LOG(LogTemp, Log, TEXT("Found %d card asset IDs"), CardIds.Num());

	for (const FPrimaryAssetId& AssetId : CardIds)
	{
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(AssetId);
		UE_LOG(LogTemp, Log, TEXT("Loading card asset: %s"), *AssetPath.ToString());

		UCard* Card = Cast<UCard>(AssetManager.GetStreamableManager().LoadSynchronous(AssetPath));
		if (Card)
		{
			LoadedCards.Emplace(Card);
			UE_LOG(LogTemp, Log, TEXT("Loaded card: %s"), *Card->CardName);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load card asset: %s"), *AssetPath.ToString());
		}
	}
	UE_LOG(LogTemp, Log, TEXT("FUNC: 'LoadAllCards'\tTotal cards loaded: %d"), LoadedCards.Num());
	return LoadedCards;
}