#include "EnginePch.h"
#include "ActorComponent/RenderComponent.h"

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

void URenderComponent::SetMeshName(string NewMeshName)
{
	MeshName = NewMeshName;
}

string URenderComponent::GetMeshName() const
{
	return MeshName;
}