// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GGJ2025CameraComponent.generated.h"

UCLASS(minimalapi)
class UGGJ2025CameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float CameraLocationReturnInterpSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	float CameraRotationReturnInterpSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float CameraLocationTargetInterpSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	float CameraRotationTargetInterpSpeed = 1.0f;

	UGGJ2025CameraComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool HasFocusTarget() const { return bCurrentTargetActivated; }

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetFocusTarget() const { return CurrentTargetAttachParent; }

	// duration: duration of the target change, -1 means no time limit
	UFUNCTION(BlueprintCallable)
	void ChangeFocusTarget(USceneComponent* newTarget, FTransform transform, bool bKeepRelativeTransform, float duration);

	UFUNCTION(BlueprintCallable)
	void ReturnFocus();

private:

	bool bOriginalValueInitialized = false;

	UPROPERTY(Transient)
	USceneComponent* OriginalAttachParent;

	FTransform OriginalRelativeTransform;

	bool bCurrentTargetActivated = false;

	UPROPERTY(Transient)
	USceneComponent* CurrentTargetAttachParent;

	FTransform CurrentTargetRelativeTransform;

	float CurrentTargetDurationTimeLeft;
};



