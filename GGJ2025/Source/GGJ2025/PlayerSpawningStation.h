
#pragma once

#include "CoreMinimal.h"
#include "PlayerSpawningStation.generated.h"

UCLASS(minimalapi)
class APlayerSpawningStation : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USceneComponent*> SpawningLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USceneComponent*> WaitingLocations;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGGJ2025Passenger> SpawningClass;

	APlayerSpawningStation();

	UFUNCTION(BlueprintCallable)
	class AGGJ2025Passenger* SpawnPassenger();

	UFUNCTION(BlueprintCallable)
	void SendPassengersToWaitingDestinations();

	UFUNCTION(BlueprintCallable)
	void ClearPassengers();

private:
	UPROPERTY(Transient)
	TArray<class AGGJ2025Passenger*> SpawnedPassengers;
};



