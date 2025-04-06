// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "AB_GameInstance.h"

// Sets default values
AAB_ProjectileBase::AAB_ProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	m_bullet->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	m_bullet->OnComponentHit.AddDynamic(this, &AAB_ProjectileBase::OnHit);

	m_movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement component"));

	m_isLastProjectile = false;

}



// Called when the game starts or when spawned
void AAB_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AAB_ProjectileBase::Init(float initialSpeed, float maxspeed)
{
	PrimaryActorTick.bCanEverTick = true;

	m_movementComponent->InitialSpeed = initialSpeed;
	m_movementComponent->MaxSpeed = maxspeed;

	m_movementComponent->SetVelocityInLocalSpace(FVector(initialSpeed, 0, 0));
	m_movementComponent->UpdateComponentVelocity();
	m_movementComponent->bSimulationEnabled = true;
	m_movementComponent->bRotationFollowsVelocity = true;

	m_clock = 0;

}

void AAB_ProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	HandleHit( HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

}

void AAB_ProjectileBase::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	//Logique ici 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AAB_ProjectileBase::DestroyActor, 5.0f, false);
	}

}

void AAB_ProjectileBase::OnUse()
{
	HandleUse();
}

void AAB_ProjectileBase::HandleUse()
{
	
}

void AAB_ProjectileBase::DestroyActor()
{
	if (m_isLastProjectile) {
		UAB_GameInstance* GameInstance = Cast<UAB_GameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			GameInstance->OnLooseCondDelegate.Broadcast();
		}
	}

	Destroy();

}

// Called every frame
void AAB_ProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_clock += DeltaTime;

	if (GetVelocity() == FVector(0, 0, 0) || m_clock >= 7) {
		DestroyActor();
	}

}



