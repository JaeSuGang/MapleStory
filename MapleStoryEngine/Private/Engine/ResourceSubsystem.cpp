#include "EnginePch.h"
#include "Engine/ResourceSubsystem.h"

void UResourceSubsystem::Tick(float fDeltaTime)
{
}

void UResourceSubsystem::LateInit()
{
}

unordered_map<string, FMesh>& UResourceSubsystem::GetMeshes()
{
	return Meshes;
}
