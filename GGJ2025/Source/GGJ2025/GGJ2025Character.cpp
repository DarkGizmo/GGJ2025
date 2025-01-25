// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ2025Character.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "UObject/UObjectIterator.h"

#include "GGJ2025CameraComponent.h"
#include "GGJ2025InteractableComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGGJ2025Character

AGGJ2025Character::AGGJ2025Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a follow camera
	NewCamera = CreateDefaultSubobject<UGGJ2025CameraComponent>(TEXT("NewCamera"));
	NewCamera->SetupAttachment(RootComponent);
	NewCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGGJ2025Character::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AGGJ2025Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AGGJ2025Character::Interact);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGGJ2025Character::Move);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGGJ2025Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector playerLocation = GetActorLocation();
	FVector playerForward = GetActorForwardVector();
	UGGJ2025InteractableComponent* bestComponent = nullptr;
	float bestScore = 0.0f;

	float maxInteractionDistanceSqr = FMath::Square(MaxInteractionDistance);

	for (TObjectIterator<UGGJ2025InteractableComponent> It; It; ++It)
	{
		// You can now access each actor through 'It'
		if (UGGJ2025InteractableComponent* interactionComponent = *It)
		{
			if (interactionComponent->GetWorld() != GetWorld())
			{
				continue;
			}

			FVector toInteractible = interactionComponent->GetComponentLocation() - playerLocation;
			float distance2DSqr = toInteractible.SizeSquared2D();
			if (distance2DSqr > maxInteractionDistanceSqr)
			{
				continue;
			}

			float distance = FMath::Sqrt(distance2DSqr);
			float distanceScore = 1.0f - distance / MaxInteractionDistance;
			float dotScore = (toInteractible / distance) | playerForward;
			float currentScore = (distanceScore + dotScore) * 0.5f;

			if (currentScore > bestScore)
			{
				bestScore = currentScore;
				bestComponent = interactionComponent;
			}
		}
	}

	if (bestComponent != InteractableInFocus)
	{
		InteractableInFocus = bestComponent;
		OnInteractibleInFocusChanged(InteractableInFocus);
	}
}

void AGGJ2025Character::Interact()
{
	if (InteractableInFocus != nullptr)
	{
		InteractableInFocus->OnInteractionEvent.Broadcast(this);
		InteractableInFocus->OnInteract(this);
	}
}

void AGGJ2025Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (NewCamera != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = NewCamera->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}