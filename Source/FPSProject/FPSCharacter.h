

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

public:
	virtual void BeginPlay();
	
protected:
	virtual void SetupPlayerInputComponent (class UInputComponent* InInputComponent);
	UFUNCTION()
	void MoveForward(float InDelta);
	UFUNCTION()
	void MoveRight(float InDelta);
	UFUNCTION()
	void OnStartJump();
	UFUNCTION()
	void OnStopJump();
};
