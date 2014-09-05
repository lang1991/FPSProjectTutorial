

#include "FPSProject.h"
#include "FPSGameMode.h"

AFPSGameMode::AFPSGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//DefaultPawnClass = AFPSCharacter::StaticClass();
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/BluePrints/BP_FPSCharacter.BP_FPSCharacter'"));
	if(PlayerPawnObject.Object)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}
}


void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World"));
	}
}