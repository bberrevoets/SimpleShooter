// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterAIController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
	if (PlayerPawn)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			MoveToActor(PlayerPawn, AcceptanceRadius);
			SetFocus(PlayerPawn);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	}
}
