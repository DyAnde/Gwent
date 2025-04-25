// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

UCard::UCard()
{
	// Default card values
	CardName = "Jesus";
	CardPower = 0;
	CardType = ECardType::Unit;
	CardFaction = ECardFaction::Neutral;
	CardRow = ECardRow::PlayerOneDeck;
	HomeRow = ECardHomeRow::Infantry;
	CardAbility = ECardAbility::None;
}

ECardRow UCard::GetCardRowFromHomeRow(ECardHomeRow HomeRow, bool bIsPlayerOne)
{
    switch (HomeRow)
    {
    case ECardHomeRow::Infantry:
        return bIsPlayerOne ? ECardRow::PlayerOneInfantry : ECardRow::PlayerTwoInfantry;
    case ECardHomeRow::Fleet:
        return bIsPlayerOne ? ECardRow::PlayerOneFleet : ECardRow::PlayerTwoFleet;
    case ECardHomeRow::Weather:
        return ECardRow::Weather;
    default:
        return ECardRow::PlayerOneDeck; // Default fallback
    }
}