// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AB_ProjectileBase.h"
#include "AB_Bomb.h"
#include "AB_ProjectileBomb.generated.h"

/**
 * 
 */
UCLASS()
class EXOPHYSICSCPP_API AAB_ProjectileBomb : public AAB_ProjectileBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAB_Bomb> m_bombModel;

	void HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	void HandleUse() override;

};
