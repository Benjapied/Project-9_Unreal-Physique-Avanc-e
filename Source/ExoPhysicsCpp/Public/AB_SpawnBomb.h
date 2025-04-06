// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AB_SpawnBomb.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXOPHYSICSCPP_API UAB_SpawnBomb : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAB_SpawnBomb();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	TSubclassOf<class AAB_ProjectileBase> ProjectileClass;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SpawnBomb(AActor* Actor);

		
};
