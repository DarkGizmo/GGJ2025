
#include "PlayerSpawningStation.h"
#include "GGJ2025Passenger.h"

APlayerSpawningStation::APlayerSpawningStation()
{

}

AGGJ2025Passenger* APlayerSpawningStation::SpawnPassenger()
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = nullptr;          // Specify the owner, if any
    SpawnParams.Instigator = nullptr;     // Specify the instigator, if needed
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    FTransform spawnTransform;
    if (SpawningLocations.Num() > 0)
    {
        if (USceneComponent* component = 
            SpawningLocations[FMath::Min(SpawnedPassengers.Num(), SpawningLocations.Num() - 1)])
        {
            spawnTransform = component->GetComponentTransform();
        }
        else
        {
            spawnTransform = GetActorTransform();
        }
    }
    else
    {
        spawnTransform = GetActorTransform();
    }

    // Spawn the actor
    AGGJ2025Passenger* newPassenger = 
        GetWorld()->SpawnActor<AGGJ2025Passenger>(SpawningClass
            , spawnTransform.GetLocation(), spawnTransform.GetRotation().Rotator(), SpawnParams);

    SpawnedPassengers.Add(newPassenger);

    return newPassenger;
}

void APlayerSpawningStation::SendPassengersToWaitingDestinations()
{
    for (int i = 0; i < SpawnedPassengers.Num(); ++i)
    {
        AGGJ2025Passenger* passenger = SpawnedPassengers[i];
        if (passenger != nullptr)
        {
            USceneComponent* destinationComponent;
            if (WaitingLocations.Num() > 0)
            {
                destinationComponent = WaitingLocations[FMath::Min(i, WaitingLocations.Num() - 1)];
            }
            else
            {
                destinationComponent = GetRootComponent();
            }
            passenger->GoToDestination(destinationComponent->GetComponentLocation(), destinationComponent->GetComponentRotation());
        }
    }
}

void APlayerSpawningStation::ClearPassengers()
{
    for (AGGJ2025Passenger* passenger : SpawnedPassengers)
    {
        if (passenger != nullptr)
        {
            passenger->Destroy();
        }
    }

    SpawnedPassengers.Empty();
}
