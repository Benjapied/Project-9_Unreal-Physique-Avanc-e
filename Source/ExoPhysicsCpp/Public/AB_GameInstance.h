// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AB_GameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWinCond);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLooseCond);
/**
 * 
 */
UCLASS()
class EXOPHYSICSCPP_API UAB_GameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	float m_Score;
public:
	UFUNCTION()
	void Win();

	UFUNCTION()
	void Loose();

	UAB_GameInstance();

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MapWin;
	UFUNCTION(BlueprintCallable)
	float GetScore();
	void AddtoScore(float value);
	FOnWinCond OnWinCondDelegate;
	FOnLooseCond OnLooseCondDelegate;

};
