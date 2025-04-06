// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AB_SpawnBombOnTrigger.h"
#include "Collision.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "AB_Balloon.generated.h"

UCLASS()
class EXOPHYSICSCPP_API AAB_Balloon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB_Balloon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UBoxComponent* BaseBalloon;
	USphereComponent* BalloonSphere;

};
