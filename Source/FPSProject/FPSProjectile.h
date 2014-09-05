

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	TSubobjectPtr<USphereComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	
public:
	void InitVelocity(const FVector& InShootDirection);
};
