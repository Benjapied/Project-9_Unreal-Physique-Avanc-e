// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AB_ProjectileBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUse);

UCLASS()
class EXOPHYSICSCPP_API AAB_ProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAB_ProjectileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* m_movementComponent;

	UPROPERTY(BlueprintAssignable)
	FOnHit OnHitDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnUse OnUseDelegate;

	bool m_isLastProjectile;

	float m_clock;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle MyTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Init(float initialSpeed, float maxspeed);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnUse();
	virtual void HandleUse();

	UFUNCTION()
	virtual void DestroyActor();

};
