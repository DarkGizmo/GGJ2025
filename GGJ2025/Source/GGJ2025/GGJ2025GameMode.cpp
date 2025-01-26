// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ2025GameMode.h"
#include "GGJ2025Character.h"
#include "UObject/ConstructorHelpers.h"

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

TArray<class AGGJ2025Passenger*> AGGJ2025GameMode::GetPassengers()
{
	if (m_SpawningStation)
	{
		return m_SpawningStation->GetSpawnedPassengers();
	}

	return TArray<class AGGJ2025Passenger*>();
}

void AGGJ2025GameMode::SpawnLevel(int32 levelIndex, APlayerSpawningStation* spawningStation, FTransform trainSpawnTransform)
{
	m_CurrentIndex = levelIndex;

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
