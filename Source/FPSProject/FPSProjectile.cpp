

#include "FPSProject.h"
#include "FPSProjectile.h"


AFPSProjectile::AFPSProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CollisionComp = PCIP.CreateDefaultSubobject<USphereComponent> (this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0f);
	RootComponent = CollisionComp;

	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent> (this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;
}


void AFPSProjectile::InitVelocity(const FVector& InShootDirection)
{
	if(ProjectileMovement)
	{
		ProjectileMovement->Velocity = InShootDirection * ProjectileMovement->InitialSpeed;
	}
}
