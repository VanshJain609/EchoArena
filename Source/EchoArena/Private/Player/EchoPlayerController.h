// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "EchoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AEchoPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//Only Call on Server
	void OnPossess(APawn* NewPawn) override;

	//Only Called on the Client
	void AcknowledgePossession(APawn* NewPawn) override;

private:
	UPROPERTY()
	class AEchoPlayerCharacter* EchoPlayerCharacter;
};
