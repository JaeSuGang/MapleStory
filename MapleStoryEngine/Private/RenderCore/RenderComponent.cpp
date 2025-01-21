#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/ResourceSubsystem.h"
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"
#include "RenderCore/Texture.h"
#include "RenderCore/Animation.h"

URenderComponent::URenderComponent()
	:
	Material{},
	IsVisible{true}
{
	MeshID = 0;
}

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

int URenderComponent::GetSortingLayer() const
{
	return SortingLayer;
}

int URenderComponent::GetZValue() const
{
	return ZValue;
}

int URenderComponent::GetZIndex() const
{
	return ZIndex;
}

void URenderComponent::AddAnimationByFolder(EAnimationName Name, string strFolderPath, int nTimePerFrame)
{
	Animation->AddAnimationByFolder(Name, strFolderPath, nTimePerFrame);
}

void URenderComponent::PlayAnimation(float fDeltaTime)
{
	Animation->Play(fDeltaTime);
}

void URenderComponent::EnableAnimation()
{
	Animation = std::make_shared<UAnimation>();
	Animation->SetMaterialToApply(Material.get());
	Animation->SetRenderComponent(this);
}

void URenderComponent::EnableMaterial()
{
	Material = std::make_shared<UMaterial>();
}

void URenderComponent::SetActorScaleByTextureSize()
{
	UTexture* Texture = GEngine->RenderSubsystem->Textures[Material->TextureID].get();

	Owner->SetScale({ (float)Texture->Width, (float)Texture->Height, 0.0001f });
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

void URenderComponent::BeginPlay()
{
	Super::BeginPlay();
}

/* SortingLayer 0 : BackGround */
/* SortingLayer 0 ~ 7 : 맵 지정 */
/* SortingLayer 8 : 몹 */
/* SortingLayer 9 : 캐릭터 */
/* SortingLayer 10 : 스킬 */
/* SortingLayer 11 : 데미지 */
/* SortingLayer 12 : 디버그 레이어 */
void URenderComponent::SetSortingLayer(int nLayer)
{
	SortingLayer = nLayer;
}

void URenderComponent::SetZValue(int nZValue)
{
	ZValue = nZValue;
}

void URenderComponent::SetZIndex(int nZIndex)
{
	ZIndex = nZIndex;
}

void URenderComponent::AddAnimationEvent(EAnimationName _AnimationName, int _Sequence, std::function<void()> _Function)
{
	Animation->AddAnimationEvent(_AnimationName, _Sequence, _Function);
}

void URenderComponent::AddAnimationEvent(FAnimationEvent _AnimationEvent)
{
	Animation->AddAnimationEvent(_AnimationEvent);
}

bool URenderComponent::GetHasPassedLastFrame() const
{
	return Animation->HasPassedLastFrame;
}

EAnimationName URenderComponent::GetCurrentAnimation() const
{
	return Animation->CurrentAnimation;
}

void URenderComponent::SetCurrentAnimation(EAnimationName Name)
{
	Animation->SetCurrentAnimation(Name);
}

void URenderComponent::SetHeightTileCount(int nCount)
{
	Material->HeightTileCount = nCount;
}

void URenderComponent::SetWidthTileCount(int nCount)
{
	Material->WidthTileCount = nCount;
}

float URenderComponent::GetAlphaValue() const
{
	return Material->AlphaValue;
}

void URenderComponent::SetAlphaValue(float _Val)
{
	Material->AlphaValue = _Val;
}

void URenderComponent::AddAlphaValue(float _Val)
{
	Material->AlphaValue += _Val;
}
