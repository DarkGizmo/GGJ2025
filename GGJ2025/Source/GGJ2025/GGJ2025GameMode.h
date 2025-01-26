// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GGJ2025Train.h"
#include "PlayerSpawningStation.h"
#include "GGJ2025GameMode.generated.h"

USTRUCT(BlueprintType)
struct FGGJ2025Level
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGGJ2025Train> Train;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AGGJ2025Passenger>> Passengers;

	FGGJ2025Level()
	{
		LevelIndex = 1;
	}
};

UCLASS(minimalapi)
class AGGJ2025GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGGJ2025Level> Levels;

	UFUNCTION(BlueprintCallable)
	void SpawnLevel(int32 levelIndex, APlayerSpawningStation* spawningStation, FTransform trainSpawnTransform);

	UFUNCTION(BlueprintCallable)
	float EvaluateLevel();

public:
	AGGJ2025GameMode();

	UFUNCTION(BlueprintCallable)
	class AGGJ2025Train* GetTrain();

	UFUNCTION(BlueprintCallable)
	TArray<class AGGJ2025Passenger*> GetPassengers() const;

	UFUNCTION(BlueprintCallable)
	bool CanBellBeRung() const;

	UFUNCTION(BlueprintCallable)
	void RingBell();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBellRung();

private:
	int32 m_CurrentIndex;

	UPROPERTY(Transient)
	class AGGJ2025Train* m_Train;

	UPROPERTY(Transient)
	class APlayerSpawningStation* m_SpawningStation;
};



