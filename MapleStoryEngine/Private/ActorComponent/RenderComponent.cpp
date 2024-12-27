#include "EnginePch.h"
#include "ActorComponent/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/ResourceSubsystem.h"

URenderComponent::URenderComponent()
{

}

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

void URenderComponent::SetMeshName(const char* lpszNewName)
{
	MeshName = lpszNewName;
}

ENGINE_API const char* URenderComponent::GetMeshName()
{
	return MeshName.data();
}