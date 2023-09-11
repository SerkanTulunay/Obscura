// Copyright Epic Games, Inc. All Rights Reserved.

#include "ObscuraGameMode.h"
#include "ObscuraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AObscuraGameMode::AObscuraGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
