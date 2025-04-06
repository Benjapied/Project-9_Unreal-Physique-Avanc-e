// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_GameInstance.h"
#include "Kismet/GameplayStatics.h"

UAB_GameInstance::UAB_GameInstance()
{
	OnWinCondDelegate.AddDynamic(this, &UAB_GameInstance::Win);
	OnLooseCondDelegate.AddDynamic(this, &UAB_GameInstance::Loose);
}

float UAB_GameInstance::GetScore()
{
	return m_Score;
}

void UAB_GameInstance::AddtoScore(float value)
{
	m_Score += value;
}

void UAB_GameInstance::Win()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}
	UGameplayStatics::OpenLevel(GetWorld(), "Win");
}

void UAB_GameInstance::Loose()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}
	UGameplayStatics::OpenLevel(GetWorld(), "Loose");
}
