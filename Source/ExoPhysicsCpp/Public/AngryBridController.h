// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "AngryBridController.generated.h"

/**
 * 
 */
UCLASS()
class EXOPHYSICSCPP_API AAngryBridController : public APlayerController
{
	GENERATED_BODY()
	
public :

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	class UInputAction* m_lookHorizontalInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	class UInputAction* m_scopeAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Input")
	class UInputAction* m_useAction;

	class AAngryBirdCharacter* m_character;

	void Turn(const FInputActionValue& Value);

	void Scope(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void Use(const FInputActionValue& Value);

};
