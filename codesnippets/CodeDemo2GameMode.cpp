// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "CodeDemo2.h"
#include "CodeDemo2GameMode.h"
#include "CodeDemo2Character.h"

ACodeDemo2GameMode::ACodeDemo2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
