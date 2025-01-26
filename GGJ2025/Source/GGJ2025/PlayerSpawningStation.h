
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
	void SpawnPassengers(TArray<TSubclassOf<class AGGJ2025Passenger>> passengers);

	UFUNCTION(BlueprintCallable)
	void SendPassengersToWaitingDestinations();

	UFUNCTION(BlueprintCallable)
	void ClearPassengers();

	UFUNCTION(BlueprintCallable)
	TArray<class AGGJ2025Passenger*> GetSpawnedPassengers();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPassengerSpawned(class AGGJ2025Passenger* passenger);

private:
	void SpawnPassengerInternal(TSubclassOf<class AGGJ2025Passenger> passenger);

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<class AGGJ2025Passenger*> SpawnedPassengers;
};



