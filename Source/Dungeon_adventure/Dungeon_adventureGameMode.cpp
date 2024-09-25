// Copyright Epic Games, Inc. All Rights Reserved.

#include "Dungeon_adventureGameMode.h"
#include "Dungeon_adventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeon_adventureGameMode::ADungeon_adventureGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
