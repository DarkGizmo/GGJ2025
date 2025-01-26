#include "GGJ2025CameraComponent.h"

UGGJ2025CameraComponent::UGGJ2025CameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UGGJ2025CameraComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCurrentTargetActivated)
	{
		const FTransform& currentTranform = GetRelativeTransform();
		if (!currentTranform.Equals(CurrentTargetRelativeTransform, 0.0001f))
		{
			FVector interpLocation = FMath::VInterpTo(currentTranform.GetLocation(), CurrentTargetRelativeTransform.GetLocation(), DeltaTime, CameraLocationTargetInterpSpeed);
			FQuat interpRotation = FMath::QInterpTo(currentTranform.GetRotation(), CurrentTargetRelativeTransform.GetRotation(), DeltaTime, CameraRotationTargetInterpSpeed);
			SetRelativeLocationAndRotation(interpLocation, interpRotation, false);
		}

		if (CurrentTargetDurationTimeLeft > 0.0f)
		{
			CurrentTargetDurationTimeLeft -= DeltaTime;
			if (CurrentTargetDurationTimeLeft <= 0.0f)
			{
				ReturnFocus();
			}
		}
	}
	else if(bOriginalValueInitialized)
	{
		const FTransform& currentTranform = GetRelativeTransform();
		if (!currentTranform.Equals(OriginalRelativeTransform, 0.0001f))
		{
			FVector interpLocation = FMath::VInterpTo(currentTranform.GetLocation(), OriginalRelativeTransform.GetLocation(), DeltaTime, CameraLocationReturnInterpSpeed);
			FQuat interpRotation = FMath::QInterpTo(currentTranform.GetRotation(), OriginalRelativeTransform.GetRotation(), DeltaTime, CameraRotationReturnInterpSpeed);
			SetRelativeLocationAndRotation(interpLocation, interpRotation, false);
		}
	}
}

void UGGJ2025CameraComponent::ChangeFocusTarget(USceneComponent* newTarget, FTransform transform, bool bKeepRelativeTransform, float duration)
{
	if (!bOriginalValueInitialized)
	{
		OriginalAttachParent = GetAttachParent();
		OriginalRelativeTransform = GetRelativeTransform();
		bOriginalValueInitialized = true;
	}

	bCurrentTargetActivated = true;
	CurrentTargetAttachParent = newTarget;
	if (bKeepRelativeTransform)
	{
		CurrentTargetRelativeTransform = OriginalRelativeTransform;
	}
	else
	{
		CurrentTargetRelativeTransform = transform;
	}
	
	CurrentTargetDurationTimeLeft = duration;

	if (newTarget != nullptr)
	{
		AttachToComponent(newTarget, FAttachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void UGGJ2025CameraComponent::ReturnFocus()
{
	bCurrentTargetActivated = false;
	CurrentTargetAttachParent = nullptr;

	AttachToComponent(OriginalAttachParent, FAttachmentTransformRules::KeepWorldTransform);
}