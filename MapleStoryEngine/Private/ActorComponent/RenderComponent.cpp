#include "EnginePch.h"
#include "ActorComponent/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/RenderSubsystem.h"
#include "Actor/Actor.h"

URenderComponent::URenderComponent()
	:
	Material{}
{
	MeshID = 0;
}

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

void URenderComponent::SetActorScaleByTextureSize()
{
	UTexture* Texture = GEngine->RenderSubsystem->Textures[Material.TextureID].get();

	Owner->SetScale((float)Texture->Width, (float)Texture->Height, 1.0f);
}

void URenderComponent::SetBlendMode(bool bIsTransculent)
{
	if (bIsTransculent == false)
		Material.BlendMode = FMaterial::EBlendMode::Opaque;

	if (bIsTransculent == true)
		Material.BlendMode = FMaterial::EBlendMode::Transculent;
}

ENGINE_API void URenderComponent::SetPixelShaderByName(string strShaderName)
{
	Material.PSShaderID = GEngine->RenderSubsystem->GetPixelShaderIDByName(strShaderName);
}

ENGINE_API void URenderComponent::SetTextureByName(string strShaderName)
{
	Material.TextureID = GEngine->RenderSubsystem->GetTextureIDByName(strShaderName);
}

ENGINE_API void URenderComponent::SetMaterial(FMaterial MaterialToApply)
{
	Material = MaterialToApply;
}

ENGINE_API void URenderComponent::SetMeshIDByName(string strName)
{
	MeshID = GEngine->ResourceSubsystem->GetMeshIDByName(strName);
}