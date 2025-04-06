// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryBridController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AngryBirdCharacter.h"

void AAngryBridController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find Enhanced Input Subsystem!"));
		}
	}

	m_character = Cast<AAngryBirdCharacter>(GetCharacter());

	if (!m_character) {

		UE_LOG(LogTemp, Error, TEXT("Character not found"));

	}

}

void AAngryBridController::SetupInputComponent()
{
	
	InputComponent = NewObject<UEnhancedInputComponent>(this, UEnhancedInputComponent::StaticClass());
	InputComponent->RegisterComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		EnhancedInputComponent->BindAction(m_lookHorizontalInputAction, ETriggerEvent::Triggered, this, &AAngryBridController::Turn);
		EnhancedInputComponent->BindAction(m_scopeAction, ETriggerEvent::Started, this, &AAngryBridController::Scope);
		EnhancedInputComponent->BindAction(m_scopeAction, ETriggerEvent::Completed, this, &AAngryBridController::Shoot);
		EnhancedInputComponent->BindAction(m_useAction, ETriggerEvent::Started, this, &AAngryBridController::Use);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."));
	}
}

void AAngryBridController::Turn(const FInputActionValue& Value)
{
	m_character->Turn(Value.Get<FVector2D>());
}

void AAngryBridController::Scope(const FInputActionValue& Value)
{
	m_character->Scoping();
}

void AAngryBridController::Shoot(const FInputActionValue& Value)
{
	m_character->Shoot();
}

void AAngryBridController::Use(const FInputActionValue& Value)
{
	m_character->Use();
}
