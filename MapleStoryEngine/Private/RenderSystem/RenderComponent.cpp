#include "EnginePch.h"
#include "RenderSystem/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/ResourceSubsystem.h"
#include "RenderSystem/RenderSubsystem.h"
#include "Actor/Actor.h"
#include "RenderSystem/Texture.h"
#include "RenderSystem/Animation.h"

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

void URenderComponent::SetAnimation(shared_ptr<UAnimation> _Animation)
{
	if (_Animation.get() == nullptr)
	{
		Animation = std::make_shared<UAnimation>();
		Animation->SetMaterialToApply(Material.get());
	}
	else
	{
		Animation = _Animation;
		Animation->SetMaterialToApply(Material.get());
	}
}

void URenderComponent::SetMaterial(shared_ptr<UMaterial> _Material)
{
	if (_Material.get() == nullptr)
		Material = std::make_shared<UMaterial>();
	else
		Material = _Material;
}

void URenderComponent::SetActorScaleByTextureSize()
{
	UTexture* Texture = GEngine->RenderSubsystem->Textures[Material->TextureID].get();

	Owner->SetScale((float)Texture->Width, (float)Texture->Height, 1.0f);
}

void URenderComponent::SetBlendMode(bool bIsTransculent)
{
	this->SetMaterialIfNull();

	Material->SetBlendMode(bIsTransculent);
}

void URenderComponent::SetPixelShaderByName(string strShaderName)
{
	this->SetMaterialIfNull();

	Material->SetPixelShaderByName(strShaderName);
}

void URenderComponent::SetTextureByName(string strTextureName)
{
	this->SetMaterialIfNull();

	Material->SetTextureByName(strTextureName);
}

void URenderComponent::SetMeshIDByName(string strName)
{
	this->SetMaterialIfNull();

	MeshID = GEngine->ResourceSubsystem->GetMeshIDByName(strName);
}

void URenderComponent::SetMaterialIfNull()
{
	if (Material.get() == nullptr)
	{
		this->SetMaterial(nullptr);
	}
}
