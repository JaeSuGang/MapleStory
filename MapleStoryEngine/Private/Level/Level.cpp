#include "EnginePch.h"
#include "Level/Level.h"

ULevel::ULevel()
{
	Actors.reserve(3000);
	ActorsToDestroy.reserve(100);
	ActorsToBeginPlay.reserve(100);
}
