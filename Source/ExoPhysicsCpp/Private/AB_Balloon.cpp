// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_Balloon.h"
#include "Collision.h"

// Sets default values
AAB_Balloon::AAB_Balloon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseBalloon = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseBalloon"));
	BaseBalloon->SetBoxExtent(FVector(8, 8, 8));
	SetRootComponent(BaseBalloon);

	BalloonSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BalloonSphere"));
	BalloonSphere->SetSphereRadius(20.f);
	BalloonSphere->SetRelativeLocation(FVector(0.f, 0.f, 28.f));
	BalloonSphere->SetupAttachment(BaseBalloon);


}

// Called when the game starts or when spawned
void AAB_Balloon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAB_Balloon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

