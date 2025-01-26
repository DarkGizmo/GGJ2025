#pragma once

#include "CoreMinimal.h"

#include "GGJ2025Placeable.h"

#include "GGJ2025Traits.generated.h"

UENUM(BlueprintType)
enum class EPassengerTrait : uint8 {
	NONE      UMETA(DisplayName = "NONE"),
	NOISY     UMETA(DisplayName = "NOISY"),
	LANDSCAPE UMETA(DisplayName = "LANDSCAPE"),
	BATHROOM  UMETA(DisplayName = "BATHROOM"),
	THIRSTY   UMETA(DisplayName = "THIRSTY"),
};

USTRUCT(BlueprintType)
struct FGGJ2025AssociatedTrait
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPassengerTrait> HasTraits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPassengerTrait> WantsTraits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPassengerTrait> DoesNotWantTraits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPlaceableType> PlaceableNeeds;
};
