// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
	//PrimaryActorTick.bCanEverTick = false;
	//PrimaryActorTick.bStartWithTickEnabled = false;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
    GEngine->AddOnScreenDebugMessage(
        -1, 5.f, FColor::Yellow,
        TEXT(">>> CustomPC BeginPlay()! <<<")
    );
	UE_LOG(LogTemp, Log, TEXT(">>> CustomPC BeginPlay()! <<<"));

	SetIgnoreLookInput(true);
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsInputKeyDown(EKeys::LeftMouseButton))
    {
        GEngine->AddOnScreenDebugMessage(
            -1, 0.f, FColor::Red,
            TEXT("LeftMouseButton is down")
        );
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    GEngine->AddOnScreenDebugMessage(
        -1, 5.f, FColor::Blue,
        TEXT("SetupInputComponent fired")
    );

	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

    //InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::OnLeftClick);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AMyPlayerController::OnLeftClick);
}

void AMyPlayerController::OnLeftClick()
{
    FVector Origin, Direction;
    if (DeprojectMousePositionToWorld(Origin, Direction))
    {
        const FVector End = Origin + Direction * 10000.f;

        // Draw the trace in the world for 1 second
        //DrawDebugLine(GetWorld(), Origin, End, FColor::Red, false, 1.f, 0, 2.f);

        FHitResult Hit;
        if (GetWorld()->LineTraceSingleByChannel(Hit, Origin, End, ECC_Visibility))
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 2.f, FColor::Green,
                FString::Printf(TEXT("Raw hit: %s"), *Hit.GetActor()->GetName())
            );
        }
    }
}
