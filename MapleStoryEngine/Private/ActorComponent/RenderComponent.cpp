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

ENGINE_API void URenderComponent::SetTextureName(const char* lpszNewName)
{
	TextureName = lpszNewName;
}

ENGINE_API const char* URenderComponent::GetTextureName()
{
	return TextureName.data();
}

void URenderComponent::SetMeshName(const char* lpszNewName)
{
	MeshName = lpszNewName;
}

ENGINE_API const char* URenderComponent::GetMeshName()
{
	return MeshName.data();
}