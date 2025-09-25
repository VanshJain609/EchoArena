// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EchoArena/Character/EchoCharacter.h"
#include "InputActionValue.h"
#include "EchoPlayerCharacter.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class AEchoPlayerCharacter : public AEchoCharacter
{
	GENERATED_BODY()
public:
	AEchoPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class UCameraComponent* ViewCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* GamePlayInputMappingContext;

	void HandleLookInput(const FInputActionValue& InputActionValue);
};
