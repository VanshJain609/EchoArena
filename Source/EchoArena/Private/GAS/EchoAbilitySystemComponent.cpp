// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EchoAbilitySystemComponent.h"

void UEchoAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;
	
	for (const TSubclassOf<UGameplayEffect>& EffectsClass: InitialEffects)
	{
		FGameplayEffectSpecHandle  EffectSpecHandle = MakeOutgoingSpec(EffectsClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}