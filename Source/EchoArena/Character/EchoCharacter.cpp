// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GAS/EchoAbilitySystemComponent.h"
#include "GAS/EchoAttributeSet.h"

// Sets default values
AEchoCharacter::AEchoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EchoAbilitySystemComponent = CreateDefaultSubobject<UEchoAbilitySystemComponent>("Echo Ability System Component");
	EchoAttributeSet = CreateDefaultSubobject<UEchoAttributeSet>("Echo Attribute Set");
}

void AEchoCharacter::ServerSideInit()
{
	EchoAbilitySystemComponent->InitAbilityActorInfo(this, this);
	EchoAbilitySystemComponent->ApplyInitialEffects();
}

void AEchoCharacter::ClientSideInit()
{
	EchoAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

// Called when the game starts or when spawned
void AEchoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AEchoCharacter::GetAbilitySystemComponent() const
{
	return EchoAbilitySystemComponent;
}

