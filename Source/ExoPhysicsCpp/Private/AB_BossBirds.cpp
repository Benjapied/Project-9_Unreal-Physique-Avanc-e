// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_BossBirds.h"
#include "AB_GameInstance.h"
#include "AB_ProjectileBase.h"

// Sets default values
AAB_BossBirds::AAB_BossBirds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Bird = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bird"));
	m_Bird->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	m_Bird->OnComponentHit.AddDynamic(this, &AAB_BossBirds::OnHit);

}

// Called when the game starts or when spawned
void AAB_BossBirds::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAB_BossBirds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAB_BossBirds::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		float damage = Cast<AAB_ProjectileBase>(OtherActor)->m_damage;
		m_damageTaken += damage;
		if (m_damageTaken >= 150.f) {

			UAB_GameInstance* GameInstance = Cast<UAB_GameInstance>(GetWorld()->GetGameInstance());
			if (GameInstance)
			{
				GameInstance->OnWinCondDelegate.Broadcast();
				GameInstance->AddtoScore(10000.f);
			}
			Destroy();
		}
	}
}


