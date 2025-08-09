// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUD) { HUD->RemoveFromParent(); }

	if (bIsWinner)
	{
		if (UUserWidget* WinScreen = CreateWidget(this, WinScreenClass))
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		if (UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass))
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = CreateWidget(this, HUDScreenClass);
	if (HUD) { HUD->AddToViewport(); }
}
