// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class EXOPHYSICSCPP_API AB_SpawnBombOnTrigger : public UActorComponent
{
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	TSubclassOf<class AAB_ProjectileBase> ProjectileClass;

	AB_SpawnBombOnTrigger();
	~AB_SpawnBombOnTrigger();

	void SpawnBomb(FVector SpawnLocation);
};
