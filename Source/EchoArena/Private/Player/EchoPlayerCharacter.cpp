// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EchoPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

AEchoPlayerCharacter::AEchoPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	bUseControllerRotationYaw = false;
	//To Rotate the Character according to the Controller
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//To Rotate the Character in Yaw Direction(X)
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

void AEchoPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	APlayerController* OwningPlayerController =GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GamePlayInputMappingContext);
			InputSubsystem->AddMappingContext(GamePlayInputMappingContext, 0);
		}
	}
}

void AEchoPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AEchoPlayerCharacter::HandleMoveInput);
	}
}

// Handles mouse/right-stick look input (camera rotation)
void AEchoPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	AddControllerPitchInput(-InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

// Handles WASD/left-stick movement input
void AEchoPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	InputValue.Normalize();

	// Move character relative to camera orientation
	AddMovementInput(GetMoveForwardDirection()*InputValue.Y + GetLookRightDirection()*InputValue.X);
}

// Returns the camera’s right direction (used for strafing left/right)
FVector AEchoPlayerCharacter::GetLookRightDirection() const
{
	return ViewCamera->GetRightVector();
}

// Returns the camera’s forward direction (used for forward/back movement)
FVector AEchoPlayerCharacter::GetLookForwardDirection() const
{
	return ViewCamera->GetForwardVector();
}

// Returns forward direction flattened to the ground plane
// (prevents moving up/down when looking up/down)
FVector AEchoPlayerCharacter::GetMoveForwardDirection() const
{
	return FVector::CrossProduct(GetLookRightDirection(), FVector::UpVector);
}
