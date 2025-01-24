#include "GamePch.h"
#include "Actors/Skills/HitEffect.h"
#include "RenderCore/RenderComponent.h"

AHitEffect::AHitEffect()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void AHitEffect::BeginPlay()
{
	Super::BeginPlay();
}

void AHitEffect::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);

	if (RenderComponent->GetHasPassedLastFrame())
	{
		this->Destroy();
		return;
	}
}

void AHitEffect::SetAnimation(string strPath, int SecondPerFrame)
{
	RenderComponent->EnableMaterial();

	RenderComponent->EnableAnimation();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetSortingLayer(RENDER_LAYER_HIT_EFFECT);

	RenderComponent->SetBlendMode(1);

	RenderComponent->SetTextureByName(strPath + "\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, strPath, SecondPerFrame);

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}
