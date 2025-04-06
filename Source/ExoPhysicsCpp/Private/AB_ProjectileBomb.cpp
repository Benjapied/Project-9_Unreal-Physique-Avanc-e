// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_ProjectileBomb.h"
#include <AB_GameInstance.h>

void AAB_ProjectileBomb::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{

		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		

		GetWorld()->SpawnActor<AAB_Bomb>(m_bombModel, GetActorLocation(), GetActorRotation(), ActorSpawnParams);

		DestroyActor();


		//GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AAB_ProjectileBase::DestroyActor, 5.0f, false);
	}
}

void AAB_ProjectileBomb::HandleUse()
{
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	GetWorld()->SpawnActor<AAB_Bomb>(m_bombModel, GetActorLocation(), GetActorRotation(), ActorSpawnParams);
	
	DestroyActor();

}
