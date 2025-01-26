#pragma once

#include "CoreMinimal.h"
#include "GGJ2025Item.generated.h"

UCLASS(minimalapi)
class AGGJ2025Item : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText GiveInteractionText;

	AGGJ2025Item();
};



