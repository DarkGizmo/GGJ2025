// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GGJ2025InteractableComponent.h"
#include "GGJ2025Placeable.h"
#include "TrainSeatComponent.generated.h"

UCLASS(minimalapi, Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UTrainSeatComponent : public UGGJ2025InteractableComponent
{
	GENERATED_BODY()

public:
	
	virtual void OnInteract_Implementation(class AGGJ2025Character* character) override;
	virtual bool IsInteractible_Implementation(class AGGJ2025Character* character) const override;

	UPROPERTY(BlueprintReadOnly, Transient)
	class AGGJ2025Passenger* SeatedPassenger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seat", meta = (AllowPrivateAccess = "true"))
	EPlaceableType PlaceableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seat", meta = (AllowPrivateAccess = "true"))
	TArray<EPlaceableType> LinkedPlaceableTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seat", meta = (AllowPrivateAccess = "true"))
	TArray<class UTrainSeatComponent*> NeighborSeats;
};



