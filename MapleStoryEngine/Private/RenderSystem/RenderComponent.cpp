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

void URenderComponent::AddAnimationByFolder(EAnimationName Name, string strFolderPath)
{
	Animation->AddAnimationByFolder(Name, strFolderPath);
}

void URenderComponent::PlayAnimation(float fDeltaTime)
{
	Animation->Play(fDeltaTime);
}

void URenderComponent::EnableAnimation()
{
	Animation = std::make_shared<UAnimation>();
	Animation->SetMaterialToApply(Material.get());
}

void URenderComponent::EnableMaterial()
{
	Material = std::make_shared<UMaterial>();
}

void URenderComponent::SetActorScaleByTextureSize()
{
	UTexture* Texture = GEngine->RenderSubsystem->Textures[Material->TextureID].get();

	Owner->SetScale((float)Texture->Width, (float)Texture->Height, 1.0f);
}

void URenderComponent::SetBlendMode(bool bIsTransculent)
{
	this->EnableMaterialIfNot();

	Material->SetBlendMode(bIsTransculent);
}

void URenderComponent::SetPixelShaderByName(string strShaderName)
{
	this->EnableMaterialIfNot();

	Material->SetPixelShaderByName(strShaderName);
}

void URenderComponent::SetTextureByName(string strTextureName)
{
	this->EnableMaterialIfNot();

	Material->SetTextureByName(strTextureName);
}

void URenderComponent::SetMeshIDByName(string strName)
{
	this->EnableMaterialIfNot();

	MeshID = GEngine->ResourceSubsystem->GetMeshIDByName(strName);
}

void URenderComponent::EnableMaterialIfNot()
{
	if (Material.get() == nullptr)
		this->EnableMaterial();
}

void URenderComponent::SetCurrentAnimation(EAnimationName Name)
{
	Animation->SetCurrentAnimation(Name);
}
