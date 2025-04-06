// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_SpawnBombOnTrigger.h"
#include "AB_ProjectileBomb.h"

AB_SpawnBombOnTrigger::AB_SpawnBombOnTrigger()
{
}

AB_SpawnBombOnTrigger::~AB_SpawnBombOnTrigger()
{
}

void AB_SpawnBombOnTrigger::SpawnBomb(FVector SpawnLocation)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		// Spawn the projectile at the muzzle
		AAB_ProjectileBomb* projectile = World->SpawnActor<AAB_ProjectileBomb>(ProjectileClass, SpawnLocation, {0,0,0}, ActorSpawnParams);

		if (projectile) {
			projectile->Init(0, 0);
		}

	}
}
