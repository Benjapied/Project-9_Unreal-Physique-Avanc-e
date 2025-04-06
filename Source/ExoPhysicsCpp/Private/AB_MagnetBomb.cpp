// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_MagnetBomb.h"
#include "Components/SceneComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollectionProxyData.h"


// Sets default values
AAB_MagnetBomb::AAB_MagnetBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_canExplode = true;
	m_clock = 0;
}

// Called when the game starts or when spawned
void AAB_MagnetBomb::BeginPlay()
{
	Super::BeginPlay();

	m_geometry = FindComponentByClass<UGeometryCollectionComponent>();

	if (!m_geometry) {
		UE_LOG(LogTemp, Error, TEXT("Dois yavoir un GeometryComponent"));
		return;
	}

	m_geometry->SetSimulatePhysics(true);
	m_geometry->SetNotifyBreaks(true); 
	
	m_geometry->OnChaosBreakEvent.AddDynamic(this, &AAB_MagnetBomb::StartExplosion);
	m_dynamicCollection = m_geometry->GetDynamicCollection();

	m_StartTransform.Empty();


	for (int i = 0; i < m_dynamicCollection->GetNumTransforms(); i++) {
		m_StartTransform.Add(FTransform(FQuat::Identity, FVector(0, 0, 0), FVector(1, 1, 1)));
	}

}

// Called every frame
void AAB_MagnetBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_isExploding || m_dynamicCollection->GetNumTransforms() == 0) return;

	/*m_clock += FMath::Clamp(DeltaTime, 0, 1);

	for (int32 i = 0; i < m_dynamicCollection->GetNumTransforms(); ++i)
	{
		FTransform CurrentTransform = FTransform(m_dynamicCollection->GetTransform(i));
		FVector NewPosition = FMath::Lerp(CurrentTransform.GetLocation(), FVector(0,0,0), m_clock);
		FQuat NewRotation = FMath::QInterpTo(CurrentTransform.GetRotation(), FQuat(0,0,0,1), m_clock, 2.0f);

		FVector3f NewPosition3f = FVector3f(NewPosition);
		FQuat4f NewRotation4f = FQuat4f(NewRotation);    

		m_dynamicCollection->SetTransform(i, FTransform3f(NewRotation4f, NewPosition3f, FVector3f(1, 1, 1)));

	}

	m_geometry->MarkRenderStateDirty();
	m_geometry->UpdateBounds();
	

	m_geometry->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	if (m_clock >= 1) {
		m_clock = 0;
		m_isExploding = false;
		
	}*/

}

void AAB_MagnetBomb::StartExplosion(const FChaosBreakEvent& BreakEvent)
{

	if (!m_canExplode) {
		return;
	}

	m_geometry->SetEnableGravity(false);
	m_geometry->SetNotifyRigidBodyCollision(false);

	/*
	m_canExplode = false;

	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AAB_MagnetBomb::EndExplosion, 2, false);

	FTransformDynamicCollection* DynamicCollection = m_geometry->GetDynamicCollection();

	if (DynamicCollection)
	{
		for (int32 i = 0; i < DynamicCollection->GetNumTransforms(); ++i)
		{
			FTransform FragmentTransform = FTransform(DynamicCollection->GetTransform(i));
			m_StartTransform.Add(FragmentTransform);
		}
	}*/

}
	

void AAB_MagnetBomb::EndExplosion()
{
	/*m_geometry->SetRestCollection(m_geometry->GetRestCollection());

	m_geometry->SetSimulatePhysics(true);

	m_isExploding = true;*/
}



