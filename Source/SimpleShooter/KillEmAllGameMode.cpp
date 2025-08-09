// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	const APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if (PlayerController != nullptr)
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::EndGame(const bool bIsPlayerWinner) const
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
