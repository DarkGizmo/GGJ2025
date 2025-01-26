#include "TrainSeatComponent.h"

#include "GGJ2025Character.h"
#include "GGJ2025Passenger.h"

void UTrainSeatComponent::OnInteract_Implementation(AGGJ2025Character* character)
{
	if (character->FollowingPassenger != nullptr)
	{
		character->FollowingPassenger->SetSeat(this);
	}
}

bool UTrainSeatComponent::IsInteractible_Implementation(AGGJ2025Character* character) const
{
	if (character->FollowingPassenger != nullptr)
	{
		return true;
	}

	return false;
}