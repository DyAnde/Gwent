// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACardActor::ACardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach a cube mesh to the actor
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	// Set the static mesh to the cube
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
	}

	// Set default value of CardInfo, to make VS happy
	CardInfo = nullptr;

	// Set the scale of the cube mesh
	CubeMesh->SetWorldScale3D(FVector(1.0f, 0.5f, 0.1f));

	// Set the default location of the cube mesh
	CubeMesh->SetWorldLocation(FVector(0.0f, 0.0f, 5.0f));

	// Disable gravity for the cube mesh
	CubeMesh->SetEnableGravity(false);

	// Lock the Z-axis position of the cube mesh
	CubeMesh->BodyInstance.bLockZTranslation = true;

	// Text render component items
	CardText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CardText"));
	CardText->SetupAttachment(RootComponent);
	CardText->SetText(FText::FromString("Card Name"));
	CardText->SetTextRenderColor(FColor::Black);
	CardText->SetHorizontalAlignment(EHTA_Center);
	CardText->SetVerticalAlignment(EVRTA_TextCenter);
	CardText->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	CardText->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACardActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Initialize the card actor with a card
void ACardActor::InitializeCard(UCard* Card)
{
	if (Card)
	{
		CardInfo = Card;
		UE_LOG(LogTemp, Log, TEXT("InitializeCard: Card initialized: %s"), *Card->CardName);
		CardText->SetText(FText::FromString(Card->CardName));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeCard: Card is null"));
	}
}

FString ACardActor::GetCardName() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetCardName: CardInfo is valid. Card name: %s"), *CardInfo->CardName);
		return CardInfo->CardName;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCardName: CardInfo is null. Returning default value."));
		return FString("No Card");
	}
	//return CardInfo ? CardInfo->CardName : FString("No Card");
}

int32 ACardActor::GetCardPower() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetCardPower: CardInfo is valid. Card power: %d"), CardInfo->CardPower);
		return CardInfo->CardPower;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCardPower: CardInfo is null. Returning default value."));
		return 0;
	}
	//return CardInfo ? CardInfo->CardPower : 0;
}

ECardFaction ACardActor::GetCardFaction() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetCardFaction: CardInfo is valid. Card faction: %d"), CardInfo->CardFaction);
		return CardInfo->CardFaction;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCardFaction: CardInfo is null. Returning default value."));
		return ECardFaction::Neutral;
	}
	//return CardInfo ? CardInfo->CardFaction : ECardFaction::Neutral;
}

ECardType ACardActor::GetCardType() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetCardType: CardInfo is valid. Card type: %d"), CardInfo->CardType);
		return CardInfo->CardType;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCardType: CardInfo is null. Returning default value."));
		return ECardType::Unit;
	}
	//return CardInfo ? CardInfo->CardType : ECardType::Unit;
}

ECardRow ACardActor::GetCardRow() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetCardRow: CardInfo is valid. Card row: %d"), CardInfo->CardRow);
		return CardInfo->CardRow;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCardRow: CardInfo is null. Returning default value."));
		return ECardRow::PlayerOneDeck;
	}
	//return CardInfo ? CardInfo->CardRow : ECardRow::PlayerOneDeck;
}

ECardHomeRow ACardActor::GetHomeRow() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetHomeRow: CardInfo is valid. Home row: %d"), CardInfo->HomeRow);
		return CardInfo->HomeRow;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetHomeRow: CardInfo is null. Returning default value."));
		return ECardHomeRow::Infantry;
	}
	//return CardInfo ? CardInfo->HomeRow : ECardHomeRow::Infantry;
}

ECardAbility ACardActor::GetCardAbility() const
{
	if (CardInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("GetCardAbility: CardInfo is valid. Card ability: %d"), CardInfo->CardAbility);
		return CardInfo->CardAbility;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCardAbility: CardInfo is null. Returning default value."));
		return ECardAbility::None;
	}
	//return CardInfo ? CardInfo->CardAbility : ECardAbility::None;
}

void ACardActor::FillHand(ECardFaction chosenFaction, TArray<ACardActor*> allSpawnedCards, TArray<int> uniqueIndexes)//, ACardSpawner* spawner)
{
	UE_LOG(LogTemp, Log, TEXT("FUNC: 'FillHand' called"));
	// Only need to fill the hand from the chosen faction
	UE_LOG(LogTemp, Log, TEXT("FUNC: 'FillHand' allSpawnedCards size: %d"), allSpawnedCards.Num());
	for (int i = 0; i < uniqueIndexes.Num(); i++)
	{
		UE_LOG(LogTemp, Log, TEXT("FUNC: 'FillHand' - unique index: %d - loop num: %d"), uniqueIndexes[i], i);
		// Get the card at the unique index
		int index = uniqueIndexes[i];
		ACardActor* card = allSpawnedCards[index];
		// Check if the card is valid and belongs to the chosen faction
		if (card && card->GetCardFaction() == chosenFaction)
		{
			// Set the card's row to Hand
			card->SetCardRow(ECardRow::Hand);
			// Delete that actor from the in game world
			//card->Destroy();
			/*
			card->SetActorLocation(FVector(0.0f, 0.0f, 5.0f));
			card->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
			card->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
			*/
		}
	}
	// The 10 cards in the hand need to be spawned in the correct location in game
	// Spawn the cards in the hand
	//spawner->SpawnRow(chosenFaction, ECardRow::Hand);
}

/*
* Function to set the card row
*
* @param NewRow - The new row to set the card to
* @return The new row that was set, or the current row if the new row is invalid
*/
ECardRow ACardActor::SetCardRow(ECardRow NewRow)
{
	if (CardInfo)
	{
		// Check if the new row is valid, or the home row of the card
		
		if (NewRow == ECardRow::PlayerOneDeck || NewRow == ECardRow::PlayerOneDiscard
			|| NewRow == ECardRow::PlayerTwoDeck || NewRow == ECardRow::PlayerTwoDiscard || NewRow == ECardRow::Hand
			|| (CardInfo->HomeRow == ECardHomeRow::Infantry && (NewRow == ECardRow::PlayerOneInfantry || NewRow == ECardRow::PlayerTwoInfantry))
			|| (CardInfo->HomeRow == ECardHomeRow::Fleet && (NewRow == ECardRow::PlayerOneFleet || NewRow == ECardRow::PlayerTwoFleet))
			|| (CardInfo->HomeRow == ECardHomeRow::Weather && NewRow == ECardRow::Weather))
		{
			// Only update the CardRow if it's a viable row
			CardInfo->CardRow = NewRow;
			OnMadeActive.Broadcast(this, CardInfo);
			return NewRow;
		}
		else
		{
			// Invalid row, return the current row
			UE_LOG(LogTemp, Warning, TEXT("Invalid row set for card: %s"), *CardInfo->CardName);
			return CardInfo->CardRow;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CardInfo is null"));
		return ECardRow::PlayerOneDeck; // Default to Deck if CardInfo is null
	}
}
