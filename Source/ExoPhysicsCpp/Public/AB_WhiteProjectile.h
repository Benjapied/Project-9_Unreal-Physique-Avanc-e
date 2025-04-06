// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AB_ProjectileBase.h"
#include "AB_Bomb.h"
#include "AB_WhiteProjectile.generated.h"

/**
 * 
 */
UCLASS()
class EXOPHYSICSCPP_API AAB_WhiteProjectile : public AAB_ProjectileBase
{
	GENERATED_BODY()

protected:

	bool m_canUse = true;

public:

	AAB_WhiteProjectile();

	UPROPERTY()
	TSubclassOf<AAB_Bomb> m_egg;

	void HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	void HandleUse() override;

	
};
