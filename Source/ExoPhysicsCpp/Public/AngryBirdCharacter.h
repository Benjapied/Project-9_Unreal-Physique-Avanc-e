// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/SplineMeshComponent.h"
#include "ExoPhysicsCpp/ExoPhysicsCppProjectile.h"

#include "AngryBirdCharacter.generated.h"

UENUM(BlueprintType)
enum Birds
{
	CLASSIC,
	BOMB,
	WHITE
};

UCLASS()
class EXOPHYSICSCPP_API AAngryBirdCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAngryBirdCharacter();

	float m_force;
	float m_forceProgress;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_minForce = 500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_maxForce = 1500;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_scopeSpeed = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_Xsensitivity = 2;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_Ysensitivity = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* m_slingShot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	USceneComponent* m_topSlingShot;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	TSubclassOf<class AAB_ProjectileBase> m_projectileClassic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	TSubclassOf<class AAB_ProjectileBase> m_projectileBomb;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	TSubclassOf<class AAB_ProjectileBase> m_projectileWhite;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	AAB_ProjectileBase* m_currentProjectile;

	UPROPERTY(EditAnywhere, Category="Spline")
	TEnumAsByte<ESplineMeshAxis::Type> m_forwardAxis;

	UPROPERTY(EditAnywhere, Category="Spline")
	class USplineComponent* m_spline;

	UPROPERTY(EditAnywhere, Category="Spline")
	class UMaterialInterface* m_splineMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool m_isScoping;

	TArray<Birds> m_birdsArray;
	int m_currentBird;

	TMap<Birds, TSubclassOf<AAB_ProjectileBase>> m_birdMap;

	UPROPERTY(EditAnywhere, Category="Spline")
	class UStaticMesh* m_meshSpline;

	UPROPERTY()
	TArray<USplineMeshComponent*> m_splineMeshArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void DisplayTrajectory();

	UFUNCTION(BlueprintCallable, Category="Input")
	void Scoping();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Turn(FVector2D vector);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void UpdateForce(float Dt);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Use();

};
