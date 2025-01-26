// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GGJ2025InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionEvent, class AGGJ2025Character*, character);

UCLASS(minimalapi, BlueprintType, meta = (BlueprintSpawnableComponent))
class UGGJ2025InteractableComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Event exposed to Blueprints
	UPROPERTY(EditAnywhere, Category = "Events")
	FText InteractionText;

	// Event exposed to Blueprints
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInteractionEvent OnInteractionEvent;

	UFUNCTION(BlueprintNativeEvent)
	void OnInteract(class AGGJ2025Character* character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FText GetInteractText(class AGGJ2025Character* character) const;
};



