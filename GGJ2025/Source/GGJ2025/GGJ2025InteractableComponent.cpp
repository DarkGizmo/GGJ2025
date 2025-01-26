#include "GGJ2025InteractableComponent.h"

void UGGJ2025InteractableComponent::OnInteract_Implementation(class AGGJ2025Character* character)
{
	UE_LOG(LogActor, Warning, TEXT("Interact not implemented on '%s'"), *GetName());
}

FText UGGJ2025InteractableComponent::GetInteractText_Implementation(class AGGJ2025Character* character) const
{
	return InteractionText;
}