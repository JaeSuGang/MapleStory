#include "GamePch.h"
#include "Actors/DamageFont.h"
#include "RenderCore/RenderComponent.h"

ADamageFont::ADamageFont()
{
	RemainedLifeTime = 1.0f;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void ADamageFont::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetSortingLayer(RENDER_LAYER_DAMAGE_SKIN);

	RenderComponent->SetBlendMode(1);

	RenderComponent->SetTextureByName("Resources\\Textures\\Fonts\\DamageSkin294\\" + std::to_string(Number) + ".png");

	RenderComponent->SetActorScaleByTextureSize();
}

void ADamageFont::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	Transform.Position.y += fDeltaTime * 50.0f;

	RemainedLifeTime -= fDeltaTime;

	if (RemainedLifeTime <= 0.0)
		this->Destroy();

	else if (RemainedLifeTime <= 0.5)
		RenderComponent->AddAlphaValue(fDeltaTime * -2.0f);
}

void ADamageFont::SetNumber(int nNum)
{
	Number = nNum;
}
