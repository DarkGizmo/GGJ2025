
#include "GGJ2025Passenger.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "GGJ2025CameraComponent.h"
#include "GGJ2025InteractableComponent.h"

//////////////////////////////////////////////////////////////////////////
// AGGJ2025Passenger

AGGJ2025Passenger::AGGJ2025Passenger()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	InteractionComponent = CreateDefaultSubobject<UGGJ2025InteractableComponent>(TEXT("Interaction Component"));
	InteractionComponent->SetupAttachment(RootComponent);
}

void AGGJ2025Passenger::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionComponent != nullptr)
	{
		InteractionComponent->OnInteractionEvent.AddDynamic(this, &AGGJ2025Passenger::OnInteract);
	}
}

void AGGJ2025Passenger::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (InteractionComponent != nullptr)
	{
		InteractionComponent->OnInteractionEvent.RemoveDynamic(this, &AGGJ2025Passenger::OnInteract);
	}

	Super::EndPlay(EndPlayReason);
}

void AGGJ2025Passenger::OnInteract(class AGGJ2025Character* character)
{
	BP_OnInteract();
}
