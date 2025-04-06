// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chaos/ChaosEventListenerComponent.h"
#include "Chaos/PhysicsObjectCollisionInterface.h"
#include "AB_MagnetBomb.generated.h"

UCLASS()
class EXOPHYSICSCPP_API AAB_MagnetBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB_MagnetBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool m_canExplode;
	bool m_isExploding;

	float m_clock;
	class FGeometryDynamicCollection* m_dynamicCollection;

	FTimerHandle MyTimerHandle;

	TArray<FTransform> m_StartTransform;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="GC")
	class UGeometryCollectionComponent* m_geometry;

	UFUNCTION(BlueprintCallable, Category="GC")
	void StartExplosion(const FChaosBreakEvent& BreakEvent);

	UFUNCTION()
	void EndExplosion();

};
