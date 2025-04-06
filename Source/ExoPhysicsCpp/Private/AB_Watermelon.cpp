// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_Watermelon.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "AB_GameInstance.h"

// Sets default values
AAB_Watermelon::AAB_Watermelon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAB_Watermelon::BeginPlay()
{
	Super::BeginPlay();
	
	GM_WaterMelon = FindComponentByClass<UGeometryCollectionComponent>();

	if (!GM_WaterMelon) {
		return;
	}

	GM_WaterMelon->SetSimulatePhysics(true);
	GM_WaterMelon->SetNotifyBreaks(true);

	GM_WaterMelon->OnChaosBreakEvent.AddDynamic(this, &AAB_Watermelon::OnBreak);
}

// Called every frame
void AAB_Watermelon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAB_Watermelon::OnBreak(const FChaosBreakEvent& BreakEvent)
{
	UAB_GameInstance* GameInstance = Cast<UAB_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->AddtoScore(score);
	}
}

