// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Card.generated.h"


/*
Unit is base and has power
Special is non-unit cards ("weather", scorch, decoy, etc.)
Hero is self-explanatory
*/
UENUM(BlueprintType)
enum class ECardType : uint8
{
	Unit,
	Special,
	Hero
};

// Self-explanatory SW factions
UENUM(BlueprintType)
enum class ECardFaction : uint8
{
	Empire,
	Rebellion,
	Neutral
};

/*
Scorch: Destroy the strongest card(s) on the battlefield
	- Possibly have the single row target variation
Muster: Play all cards of the same name from your deck
Spy: Play on your opponent's side of the battlefield, draw 2 cards from your deck into your hand
Tight Bond: When played with another card of the same name, double the power of both cards
Medic: Play a card from your discard pile
*/
UENUM(BlueprintType)
enum class ECardAbility : uint8
{
	None,
	Scorch,
	Muster,
	Spy,
	TightBond,
	Medic
};

// What row the card is played on
UENUM(BlueprintType)
enum class ECardRow : uint8
{
	PlayerOneInfantry,
	PlayerTwoInfantry,
	PlayerOneFleet,
	PlayerTwoFleet,
	Hand,
	PlayerOneDeck,
	PlayerTwoDeck,
	PlayerOneDiscard,
	PlayerTwoDiscard,
	Weather
};

UENUM(BlueprintType)
enum class ECardHomeRow : uint8
{
	Infantry,
	Fleet,
	Weather
};

/**
 * 
 */
UCLASS(BlueprintType)
class GWENT_API UCard : public UDataAsset
{
	GENERATED_BODY()

public:
	UCard();

	// Card properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 CardPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardFaction CardFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardType CardType;

	// What row the card is currently in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardRow CardRow;

	// What row the card is played on
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
	ECardHomeRow HomeRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardAbility CardAbility;
	
	UFUNCTION(BlueprintCallable, Category = "Card")
	static ECardRow GetCardRowFromHomeRow(ECardHomeRow EHomeRow, bool bIsPlayerOne);
};
