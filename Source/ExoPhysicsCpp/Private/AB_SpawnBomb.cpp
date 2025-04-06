// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_SpawnBomb.h"
#include "AB_ProjectileBomb.h"
#include "AB_GameInstance.h"


// Sets default values for this component's properties
UAB_SpawnBomb::UAB_SpawnBomb()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAB_SpawnBomb::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAB_SpawnBomb::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAB_SpawnBomb::SpawnBomb(AActor* Actor)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		FVector SpawnLocation = FVector(Actor->GetActorLocation().X, Actor->GetActorLocation().Y, Actor->GetActorLocation().Z - 150.f);
		AAB_ProjectileBomb* projectile = World->SpawnActor<AAB_ProjectileBomb>(ProjectileClass, SpawnLocation, {0,0,0}, ActorSpawnParams);

		if (projectile) {
			projectile->Init(0, 0);
		}

	}
}

