
#include "GGJ2025Passenger.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "GGJ2025Character.h"
#include "GGJ2025InteractableComponent.h"
#include "GGJ2025Item.h"
#include "TrainSeatComponent.h"

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

		if (player->FollowingPassenger != nullptr && player->FollowingPassenger->Seat != nullptr)
		{
			player->FollowingPassenger->SetSeat(nullptr);
		}
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
			FHitResult hitResult;
			SetActorLocation(location + (toPlayer.GetSafeNormal2D() * FollowingPlayerSpeed * DeltaTime), true, &hitResult);
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

void AGGJ2025Passenger::SetHeldItem(class AGGJ2025Item* newItem)
{
	if (HeldItem != newItem)
	{
		HeldItem = newItem;

		if (HeldItem != nullptr)
		{
			USceneComponent* pickupCompoment = FindComponentByTag<USceneComponent>(TEXT("Pickup"));
			HeldItem->AttachToComponent(pickupCompoment, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}

		OnHeldItemChanged(HeldItem);
	}
}

void AGGJ2025Passenger::SetSeat_Implementation(UTrainSeatComponent* seat)
{
	if (Seat != seat)
	{
		if (Seat != nullptr)
		{
			Seat->SeatedPassenger = nullptr;
		}

		Seat = seat;

		if (Seat != nullptr)
		{
			Seat->SeatedPassenger = this;
			StopFollowPlayer();
		}
	}
}

void AGGJ2025Passenger::RemoveHeldItem(bool bDestroy)
{
	if (bDestroy && HeldItem != nullptr)
	{
		HeldItem->Destroy();
	}

	SetHeldItem(nullptr);
}

void AGGJ2025Passenger::OnInteract(class AGGJ2025Character* character)
{
	BP_OnInteract();

	if (character != nullptr)
	{
		character->SetTalkingPassenger(this);
	}
}
