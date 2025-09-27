// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EchoPlayerController.h"
#include "Player/EchoPlayerCharacter.h"



void AEchoPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	EchoPlayerCharacter = Cast<AEchoPlayerCharacter>(NewPawn);
	if (EchoPlayerCharacter)
	{
		EchoPlayerCharacter->ServerSideInit();
	}
}

void AEchoPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	EchoPlayerCharacter = Cast<AEchoPlayerCharacter>(NewPawn);
	if (EchoPlayerCharacter)
	{
		EchoPlayerCharacter->ClientSideInit();
	}
}
