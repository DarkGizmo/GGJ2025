#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "GGJ2025Placeable.generated.h"

UENUM(BlueprintType)
enum class EPlaceableType : uint8 {
	SEAT     UMETA(DisplayName = "SEAT"),
	WINDOW   UMETA(DisplayName = "WINDOW"),
	BATHROOM UMETA(DisplayName = "BATHROOM")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UGGJ2025Placeable : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable", meta = (AllowPrivateAccess = "true"))
	EPlaceableType PlaceableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable", meta = (AllowPrivateAccess = "true"))
	AActor* AssignedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable", meta = (AllowPrivateAccess = "true"))
	TArray<UGGJ2025Placeable*> LinkedObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Placeable", meta = (AllowPrivateAccess = "true"))
	class UGGJ2025InteractableComponent* InteractionComponent;
};
