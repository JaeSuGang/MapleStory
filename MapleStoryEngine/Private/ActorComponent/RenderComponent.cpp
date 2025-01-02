#include "EnginePch.h"
#include "ActorComponent/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/RenderSubsystem.h"

URenderComponent::URenderComponent()
{

}

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

ENGINE_API void URenderComponent::SetSRVIDByName(string strName)
{
	SRVID = GEngine->RenderSubsystem->GetSRVIDByName(strName);
}

ENGINE_API void URenderComponent::SetMeshIDByName(string strName)
{
	MeshID = GEngine->ResourceSubsystem->GetMeshIDByName(strName);
}

ENGINE_API void URenderComponent::SetTextureIDByName(string strName)
{
	TextureID = GEngine->RenderSubsystem->GetTextureIDByName(strName);
}

ENGINE_API void URenderComponent::SetIndexBufferIDByName(string strName)
{
	IndexBufferID = GEngine->RenderSubsystem->GetIndexBufferIDByName(strName);
}

ENGINE_API void URenderComponent::SetVertexBufferIDByName(string strName)
{
	VertexBufferID = GEngine->RenderSubsystem->GetVertexBufferIDByName(strName);
}

ENGINE_API void URenderComponent::SetMeshInfosByName(string strName)
{
	this->SetMeshIDByName(strName);
	this->SetVertexBufferIDByName(strName);
	this->SetIndexBufferIDByName(strName);
}

ENGINE_API void URenderComponent::SetTextureInfosByName(string strName)
{
	this->SetTextureIDByName(strName);
	this->SetSRVIDByName(strName);
}