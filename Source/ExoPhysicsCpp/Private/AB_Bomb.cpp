// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_Bomb.h"

// Sets default values
AAB_Bomb::AAB_Bomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAB_Bomb::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AAB_Bomb::DestroyActor, 0.2f, false);


}

// Called every frame
void AAB_Bomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAB_Bomb::DestroyActor()
{
	Destroy();
}

