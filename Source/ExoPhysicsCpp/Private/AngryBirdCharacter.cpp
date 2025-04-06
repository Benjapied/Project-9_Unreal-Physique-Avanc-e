// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryBirdCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "AB_ProjectileBase.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AAngryBirdCharacter::AAngryBirdCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_slingShot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlingShot"));
	m_slingShot->SetupAttachment(GetRootComponent());

	m_topSlingShot = CreateDefaultSubobject<USceneComponent>(TEXT("TopSlingShot"));
	m_topSlingShot->SetupAttachment(m_slingShot);

	m_spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	m_spline->SetupAttachment(RootComponent);

	m_birdsArray = TArray<Birds>({
		Birds::CLASSIC, Birds::BOMB, Birds::WHITE,
		Birds::BOMB, Birds::BOMB, Birds::WHITE,
		Birds::CLASSIC, Birds::BOMB, Birds::BOMB
		});

	m_currentBird = 0;
}

// Called when the game starts or when spawned
void AAngryBirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_birdMap = TMap<Birds, TSubclassOf<AAB_ProjectileBase>>({
		{Birds::CLASSIC , m_projectileClassic},
		{Birds::BOMB , m_projectileBomb},
		{Birds::WHITE , m_projectileWhite},
		});

}

// Called every frame
void AAngryBirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isScoping) {
		UpdateForce(DeltaTime);
		DisplayTrajectory();
	}
}

void AAngryBirdCharacter::OnConstruction(const FTransform& Transform)
{

	//Init de la spline, on en fait 20 vides qu'on place plus tard
	for (int SplineCount = 0; SplineCount < 20; SplineCount++) {

		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		splineMesh->SetMobility(EComponentMobility::Movable);
		splineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		splineMesh->RegisterComponentWithWorld(GetWorld());
		splineMesh->AttachToComponent(m_spline, FAttachmentTransformRules::KeepRelativeTransform);

		splineMesh->SetStartAndEnd(FVector(0, 0, 0), FVector(0, 0, 0), FVector(0, 0, 0), FVector(0, 0, 0));
		splineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		splineMesh->SetStaticMesh(m_meshSpline);
		splineMesh->SetForwardAxis(m_forwardAxis);
		splineMesh->SetHiddenInGame(true);
		
		if (m_splineMaterial) {
			splineMesh->SetMaterial(0,m_splineMaterial);
		}

		m_splineMeshArray.Add(splineMesh);


	}
	
}

void AAngryBirdCharacter::DisplayTrajectory()
{
	float radius = 10;

	const FRotator SpawnRotation = m_topSlingShot->GetComponentRotation();
	const FVector SpawnLocation = m_topSlingShot->GetComponentLocation() + SpawnRotation.RotateVector(FVector(0, 0, 0));

	FVector cameraForward = UKismetMathLibrary::GetForwardVector(m_topSlingShot->GetComponentRotation());

	FPredictProjectilePathParams params = FPredictProjectilePathParams(radius, SpawnLocation, cameraForward * m_force, 4.f);
	params.DrawDebugTime = 0.02f;
	params.bTraceWithCollision = true;
	params.bTraceComplex = true;
	params.DrawDebugType = EDrawDebugTrace::None;
	params.SimFrequency = 10.f;
	params.OverrideGravityZ = 0.f;
	params.bTraceWithChannel = true;

	FPredictProjectilePathResult predictResults;
	UGameplayStatics::PredictProjectilePath(GetWorld(), params, predictResults);

	FHitResult OutHit = predictResults.HitResult;
	FVector OutLastTraceDestination = predictResults.LastTraceDestination.Location;

	for (int i = 0; i < (predictResults.PathData.Num() - 1) && i < (m_splineMeshArray.Num() - 1); i++) {

		FVector start = predictResults.PathData[i].Location;
		FVector end = predictResults.PathData[i + 1].Location;
		FVector tangent = (end - start).GetSafeNormal() * 50.0f;

		FVector localStart = m_splineMeshArray[i]->GetComponentTransform().InverseTransformPosition(start);
		FVector localEnd = m_splineMeshArray[i]->GetComponentTransform().InverseTransformPosition(end);
		FVector localTangent = m_splineMeshArray[i]->GetComponentTransform().InverseTransformVector(tangent);

		m_splineMeshArray[i]->SetStartAndEnd(localStart, localTangent, localEnd, localTangent);
	}

	if (predictResults.HitResult.bBlockingHit)
	{
		FVector HitLocation = predictResults.HitResult.ImpactPoint;
		FVector HitNormal = predictResults.HitResult.ImpactNormal;

		DrawDebugSphere(GetWorld(), HitLocation, 10.0f, 12, FColor::Red, false, 0.05f);
	}

}

void AAngryBirdCharacter::Scoping()
{
	m_isScoping = true;
	m_force = 0;
	m_forceProgress = 0;

	for (int i = 0; i < m_splineMeshArray.Num(); i++) {
		m_splineMeshArray[i]->SetHiddenInGame(false);
	}
}

void AAngryBirdCharacter::Turn(FVector2D value)
{
	FRotator RotationChange = FRotator(value.Y * m_Ysensitivity, value.X * m_Xsensitivity, 0.0f);

	FRotator CurrentRotation = m_topSlingShot->GetRelativeRotation();

	CurrentRotation.Yaw = FMath::Clamp(CurrentRotation.Yaw + RotationChange.Yaw, -60.0f, 60.0f);
	CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch + RotationChange.Pitch, -45.0f, 45.0f);

	m_topSlingShot->SetRelativeRotation(CurrentRotation);

}

void AAngryBirdCharacter::Shoot()
{

	m_isScoping = false;
	for (int i = 0; i < m_splineMeshArray.Num(); i++) {
		m_splineMeshArray[i]->SetHiddenInGame(true);
	}

	if (m_currentBird == m_birdsArray.Num()) {
		return;
	}

	// Try and fire a projectile
	if (m_projectileClassic != nullptr && m_projectileBomb != nullptr && m_projectileWhite != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{

			const FRotator SpawnRotation = m_topSlingShot->GetComponentRotation();
			const FVector SpawnLocation = m_topSlingShot->GetComponentLocation() + SpawnRotation.RotateVector(FVector(0, 0, 0));

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			AAB_ProjectileBase* projectile = World->SpawnActor<AAB_ProjectileBase>(m_birdMap[m_birdsArray[m_currentBird]], SpawnLocation, SpawnRotation, ActorSpawnParams);
			
			if (projectile) {
				m_currentProjectile = projectile;
				projectile->Init(m_force, m_force);

				m_currentBird++;	
				if (m_currentBird >= m_birdsArray.Num()) {
					projectile->m_isLastProjectile = true;
				}

			}


		}
	}

}

void AAngryBirdCharacter::UpdateForce(float Dt)
{
	m_forceProgress += Dt;
	float sinForce = (FMath::Sin(m_forceProgress) + 1 )/ 2;
	m_force = FMath::Lerp(m_minForce,m_maxForce,sinForce);

}

void AAngryBirdCharacter::Use()
{
	if (m_currentProjectile) {
		m_currentProjectile->OnUse();
	}

}


