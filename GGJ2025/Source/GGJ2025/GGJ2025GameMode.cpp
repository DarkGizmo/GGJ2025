// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ2025GameMode.h"
#include "GGJ2025Character.h"
#include "GGJ2025Passenger.h"
#include "GGJ2025Traits.h"
#include "TrainSeatComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "GGJ2025Passenger.h"

AGGJ2025GameMode::AGGJ2025GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	m_CurrentIndex = 1;
}

AGGJ2025Train* AGGJ2025GameMode::GetTrain()
{
	return m_Train;
}

TArray<class AGGJ2025Passenger*> AGGJ2025GameMode::GetPassengers() const
{
	if (m_SpawningStation)
	{
		return m_SpawningStation->GetSpawnedPassengers();
	}

	return TArray<class AGGJ2025Passenger*>();
}

bool AGGJ2025GameMode::CanBellBeRung() const
{
	for (AGGJ2025Passenger* passenger : GetPassengers())
	{
		if (passenger != nullptr && passenger->GetSeat() == nullptr)
		{
			return false;
		}
	}

	return true;
}

void AGGJ2025GameMode::RingBell()
{
	if (CanBellBeRung())
	{
		OnBellRung();
	}
}

void AGGJ2025GameMode::SpawnLevel(int32 levelIndex, APlayerSpawningStation* spawningStation, FTransform trainSpawnTransform)
{
	m_CurrentIndex = levelIndex;
	m_SpawningStation = spawningStation;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;          // Specify the owner, if any
	SpawnParams.Instigator = nullptr;     // Specify the instigator, if needed
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (auto It = Levels.CreateIterator(); It; ++It)
	{
		if (It->LevelIndex == levelIndex)
		{
			m_Train = GetWorld()->SpawnActor<AGGJ2025Train>(It->Train
				, trainSpawnTransform.GetLocation()
				, trainSpawnTransform.GetRotation().Rotator(), SpawnParams);

			spawningStation->SpawnPassengers(It->Passengers);
			
			break;
		}
	}
}

float AGGJ2025GameMode::EvaluateLevel()
{
	static float constexpr c_PerfectResult = 1.0f;
	float result = 0.f;

	auto spawnedPassengers = m_SpawningStation->GetSpawnedPassengers();
	for (auto passenger : spawnedPassengers)
	{
		auto seat = passenger->GetSeat();
		auto trait = passenger->Traits;

		int32 nbGoals = trait.WantsTraits.Num() + trait.DoesNotWantTraits.Num() + trait.PlaceableNeeds.Num();
		if (nbGoals == 0)
		{
			result += c_PerfectResult;
			continue;
		}

		int32 nbCompletedGoals = 0;
		// Iterate over want traits
		for (auto wantTrait : trait.WantsTraits)
		{
			bool hasFoundTrait = false;
			for (auto ItNeighbor = seat->NeighborSeats.CreateIterator(); ItNeighbor && !hasFoundTrait; ++ItNeighbor)
			{
				auto neighbor = *ItNeighbor;
				auto seatedNeighbor = neighbor->SeatedPassenger;
				if (seatedNeighbor)
				{
					auto neighborTrait = seatedNeighbor->Traits;
					for (auto ItHasTrait = neighborTrait.HasTraits.CreateIterator(); ItHasTrait && !hasFoundTrait; ++ItHasTrait)
					{
						if (wantTrait == *ItHasTrait)
						{
							++nbCompletedGoals;
							hasFoundTrait = true;
							break;
						}
					}
				}
			}
		}

		// Iterate over does not want traits
		for (auto doesNotWantTrait : trait.DoesNotWantTraits)
		{
			bool hasFoundTrait = false;
			for (auto ItNeighbor = seat->NeighborSeats.CreateIterator(); ItNeighbor && !hasFoundTrait; ++ItNeighbor)
			{
				auto neighbor = *ItNeighbor;
				auto seatedNeighbor = neighbor->SeatedPassenger;
				if (seatedNeighbor)
				{
					auto neighborTrait = seatedNeighbor->Traits;
					for (auto ItHasTrait = neighborTrait.HasTraits.CreateIterator(); ItHasTrait && !hasFoundTrait; ++ItHasTrait)
					{
						if (doesNotWantTrait == *ItHasTrait)
						{
							hasFoundTrait = true;
							break;
						}
					}
				}
			}

			if (!hasFoundTrait)
			{
				++nbCompletedGoals;
			}
		}

		// Iterate over placeable needs
		for (auto placeableNeeds : trait.PlaceableNeeds)
		{
			for (auto linkedPlaceable : seat->LinkedPlaceableTypes)
			{
				if (placeableNeeds == linkedPlaceable)
				{
					++nbCompletedGoals;
					break;
				}
			}
		}

		// Calculate goals average for passenger
		result += static_cast<float>(nbCompletedGoals) / nbGoals;
	}

	int32 nbPassengers = spawnedPassengers.Num();

	return result / static_cast<float>(nbPassengers);
}
