// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GGJ2025Passenger.generated.h"

UCLASS(config=Game)
class AGGJ2025Passenger : public ACharacter
{
	GENERATED_BODY()

	/** Interaction */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UGGJ2025InteractableComponent* InteractionComponent;


public:
	AGGJ2025Passenger();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

protected:

	UFUNCTION()
	void OnInteract(class AGGJ2025Character* character);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnInteract();
};

