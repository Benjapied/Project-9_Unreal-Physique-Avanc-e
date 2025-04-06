// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AB_Bomb.generated.h"

UCLASS()
class EXOPHYSICSCPP_API AAB_Bomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB_Bomb();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle MyTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void DestroyActor();

};
