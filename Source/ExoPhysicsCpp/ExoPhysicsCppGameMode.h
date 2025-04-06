// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExoPhysicsCppGameMode.generated.h"

UCLASS(minimalapi)
class AExoPhysicsCppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character")
	TSubclassOf<APawn> m_mainCharacter;

	AExoPhysicsCppGameMode();
};



