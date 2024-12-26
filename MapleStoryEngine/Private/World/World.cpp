#include "EnginePch.h"
#include "Level/Level.h"
#include "World/World.h"

vector<shared_ptr<AActor>>& UWorld::GetActors()
{
	return PersistentLevel->Actors;
}
