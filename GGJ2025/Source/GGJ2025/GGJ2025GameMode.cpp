// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ2025GameMode.h"
#include "GGJ2025Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ2025GameMode::AGGJ2025GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
