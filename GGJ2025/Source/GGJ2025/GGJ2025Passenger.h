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

	UPROPERTY(EditDefaultsOnly)
	float FollowingPlayerSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float FollowTurnInterpSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly)
	float FollowDistance = 100.0f;

	AGGJ2025Passenger();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void StartFollowPlayer(class AGGJ2025Character* player);

	UFUNCTION(BlueprintCallable)
	void StopFollowPlayer();

protected:

	UFUNCTION()
	void OnInteract(class AGGJ2025Character* character);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnInteract();

	virtual void Tick(float DeltaTime) override;

private:
	class AGGJ2025Character* PlayerToFollow;
};

