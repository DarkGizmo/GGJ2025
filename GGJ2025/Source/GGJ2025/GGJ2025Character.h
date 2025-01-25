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

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly)
	float MaxInteractionDistance = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxInteractionDot = 0.5f;


public:
	AGGJ2025Character();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractibleInFocusChanged(class UGGJ2025InteractableComponent* component);

protected:

	UFUNCTION(Category = Character)
	virtual void Interact();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return NewCamera; }

	UPROPERTY(Transient)
	class AGGJ2025Passenger* FollowingPassenger;

private:

	UPROPERTY(Transient)
	class UGGJ2025InteractableComponent* InteractableInFocus = nullptr;
};

