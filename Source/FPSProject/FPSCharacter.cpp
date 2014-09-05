

#include "FPSProject.h"
#include "FPSCharacter.h"


AFPSCharacter::AFPSCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent> (this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
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
}

void AFPSCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::OnStopJump()
{
	bPressedJump = false;
}