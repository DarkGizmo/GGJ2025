
#include "GGJ2025Passenger.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "GGJ2025Character.h"
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

void AGGJ2025Passenger::StartFollowPlayer(class AGGJ2025Character* player)
{
	if (player != nullptr)
	{
		if (PlayerToFollow != nullptr)
		{
			StopFollowPlayer();
		}

		PlayerToFollow = player;

		if (player->FollowingPassenger != nullptr)
		{
			player->FollowingPassenger->StopFollowPlayer();
		}

		player->FollowingPassenger = this;
	}
}

void AGGJ2025Passenger::StopFollowPlayer()
{
	if (PlayerToFollow)
	{
		if (PlayerToFollow->FollowingPassenger == this)
		{
			PlayerToFollow->FollowingPassenger = nullptr;
		}

		PlayerToFollow = nullptr;
	}
}

void AGGJ2025Passenger::ShowThoughts(bool bVisible)
{
	if (bShowThoughts != bVisible)
	{
		bShowThoughts = bVisible;
		BP_OnShowThoughtsStateChanged();
	}
}

FText AGGJ2025Passenger::GetSpeechText_Implementation() const
{
	return FText::FromString(TEXT("Not Implemented yet!"));
}

void AGGJ2025Passenger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerToFollow != nullptr)
	{
		FVector location = GetActorLocation();

		FVector toPlayer = PlayerToFollow->GetActorLocation() - location;
		float distSqr2D = toPlayer.SizeSquared2D();
		if (distSqr2D > FMath::Square(FollowDistance))
		{
			SetActorLocation(location + (toPlayer.GetSafeNormal2D() * FollowingPlayerSpeed * DeltaTime), true);
		}

		toPlayer.Z = 0.0f;
		FRotator desiredRotation = toPlayer.Rotation();
		FRotator currentRotation = GetActorRotation();

		if (desiredRotation.Yaw != currentRotation.Yaw)
		{
			SetActorRotation(FMath::RInterpTo(currentRotation, desiredRotation, DeltaTime, FollowTurnInterpSpeed));
		}
	}
}

void AGGJ2025Passenger::OnInteract(class AGGJ2025Character* character)
{
	BP_OnInteract();

	if (character != nullptr)
	{
		// Camera focus
		/*
		if (character->GetFollowCamera() != nullptr)
		{
			if (character->GetFollowCamera()->HasFocusTarget())
			{
				character->GetFollowCamera()->ReturnFocus();
			}
			else
			{
				character->GetFollowCamera()->ChangeFocusTarget(GetRootComponent(), FTransform::Identity, true, -1.0f);
			}
		}
		*/
		
		if (PlayerToFollow != nullptr)
		{
			PlayerToFollow->FollowingPassenger = nullptr;
		}

		if (character == PlayerToFollow)
		{
			StopFollowPlayer();
		}
		else
		{
			StartFollowPlayer(character);
		}
	}
}
