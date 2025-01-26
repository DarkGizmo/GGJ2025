// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GGJ2025Traits.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	struct FGGJ2025AssociatedTrait Traits;

	AGGJ2025Passenger();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void StartFollowPlayer(class AGGJ2025Character* player);

	UFUNCTION(BlueprintCallable)
	void StopFollowPlayer();

	void ShowThoughts(bool bVisible);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FText GetSpeechText() const;

	UFUNCTION(BlueprintCallable)
	class UGGJ2025InteractableComponent* GetInteractionComponent() const { return InteractionComponent; }

	UFUNCTION(BlueprintImplementableEvent)
	void GoToDestination(const FVector& location, const FRotator& rotation);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
	class AGGJ2025Item* HeldItem;

	UFUNCTION(BlueprintCallable)
	void SetHeldItem(class AGGJ2025Item* newItem);

	UFUNCTION(BlueprintCallable)
	class UTrainSeatComponent* GetSeat() const { return Seat; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetSeat(class UTrainSeatComponent* seat);

	UFUNCTION(BlueprintCallable)
	void RemoveHeldItem(bool bDestroy);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHeldItemChanged(class AGGJ2025Item* newItem);

	UFUNCTION(BlueprintCallable)
	UTrainSeatComponent* GetSeat();

protected:

	UFUNCTION()
	void OnInteract(class AGGJ2025Character* character);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnInteract();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnShowThoughtsStateChanged();

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bShowThoughts = false;

	UPROPERTY(Transient)
	class AGGJ2025Character* PlayerToFollow;

	UPROPERTY(Transient)
	class UTrainSeatComponent* Seat;
};

