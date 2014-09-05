
#include "FPSProject.h"
#include "FPSCharacter.h"


AFPSCharacter::AFPSCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	Mesh->SetOwnerNoSee(true);
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("We are using FPSCharacter"));
	}
}

void AFPSCharacter::MoveForward(float InDelta)
{
	if(Controller && (InDelta != 0.0f))
	{
		FRotator rotation = Controller->GetControlRotation();
		if(CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			rotation.Pitch = 0.0f;
		}

		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(direction, InDelta);
	}
}

void AFPSCharacter::MoveRight(float InDelta)
{
	if(Controller && (InDelta != 0.0f))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(direction, InDelta);
	}
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* InInputComponent)
{
	InInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	InInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	InInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	InInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::OnStartJump);
	InInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::OnStopJump);
	InInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
}

void AFPSCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::OnFire()
{
	if(ProjectileClass)
	{
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);

		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* const World = GetWorld();
		
		if(World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile> (ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if(Projectile)
			{
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}