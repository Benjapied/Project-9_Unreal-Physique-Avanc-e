// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExoPhysicsCppGameMode.h"
#include "ExoPhysicsCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExoPhysicsCppGameMode::AExoPhysicsCppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = m_mainCharacter;

}
