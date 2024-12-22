#include "EnginePch.h"
#include "Level/Level.h"

vector<shared_ptr<AActor>>& ULevel::GetActorContainer()
{
	return Actors;
}
