// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_WhiteProjectile.h"

AAB_WhiteProjectile::AAB_WhiteProjectile()
{
	m_canUse = true;
}

void AAB_WhiteProjectile::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		if (!m_canUse) { return; }

		
		m_canUse = false;

		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AAB_ProjectileBase::DestroyActor, 2.0f, false);
		OnHitDelegate.Broadcast();
	}
}

void AAB_WhiteProjectile::HandleUse()
{

	if (!m_canUse) { return; }

	m_canUse = false;

	m_bullet->SetSimulatePhysics(true);
	m_bullet->AddImpulse(FVector(0,0,1) * 2000.0f, NAME_None, false);

	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AAB_ProjectileBase::DestroyActor, 3.0f, false);

	OnUseDelegate.Broadcast();

}
