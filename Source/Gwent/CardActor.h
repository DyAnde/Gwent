// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "CardActor.generated.h"

UCLASS()
class GWENT_API ACardActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Initialize the card actor with a card
	UFUNCTION(BlueprintCallable, Category = "Card")
	void InitializeCard(UCard* Card);

	// Static mesh for the card
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(BlueprintReadWrite, Category = "Card")
	UCard* CardInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Card", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* CardText;

	UFUNCTION(BlueprintCallable, Category = "Card")
	FString GetCardName() const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	int32 GetCardPower() const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECardFaction GetCardFaction() const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECardType GetCardType() const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECardRow GetCardRow() const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECardHomeRow GetHomeRow() const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECardAbility GetCardAbility() const;

	// Define the delegate type
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMadeActive, ACardActor*, CardActor, UCard*, Card);

	// Event Dispatcher to call when a card is made active
	UPROPERTY(BlueprintAssignable, Category = "Card")
	FOnMadeActive OnMadeActive;

	UFUNCTION(BlueprintCallable, Category = "Card")
	void FillHand(ECardFaction chosenFaction, TArray<ACardActor*> allSpawnedCards, TArray<int> uniqueIndexes);//, ACardSpawner* spawner);

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECardRow SetCardRow(ECardRow NewRow);
};