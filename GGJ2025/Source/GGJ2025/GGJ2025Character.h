// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "GGJ2025CameraComponent.h"

#include "GGJ2025Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGGJ2025Character : public ACharacter
{
	GENERATED_BODY()

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UGGJ2025CameraComponent* NewCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CancelAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly)
	float MaxInteractionDistance = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxInteractionDot = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float InteractionDotCloseThreshold = 30.0f;

	UPROPERTY(EditDefaultsOnly)
	float InteractionDotLimit = 0.707f;

public:
	AGGJ2025Character();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractibleInFocusChanged(class UGGJ2025InteractableComponent* component);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTalkingPassengerChanged(class AGGJ2025Passenger* passenger);

protected:

	UFUNCTION(Category = Character)
	virtual void Interact();

	UFUNCTION(Category = Character)
	virtual void Cancel();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UGGJ2025CameraComponent* GetFollowCamera() const { return NewCamera; }

	UFUNCTION(BlueprintCallable)
	class UGGJ2025InteractableComponent* GetInteractableInFocus() const { return InteractableInFocus;	}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
	class AGGJ2025Passenger* FollowingPassenger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
	class AGGJ2025Passenger* TalkingPassenger;

	void SetTalkingPassenger(class AGGJ2025Passenger* talkingPassenger);

private:

	UPROPERTY(Transient)
	class UGGJ2025InteractableComponent* InteractableInFocus = nullptr;
};

