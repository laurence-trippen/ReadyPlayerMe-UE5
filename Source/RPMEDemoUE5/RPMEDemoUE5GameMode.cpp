// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPMEDemoUE5GameMode.h"
#include "RPMEDemoUE5Character.h"
#include "UObject/ConstructorHelpers.h"

ARPMEDemoUE5GameMode::ARPMEDemoUE5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
