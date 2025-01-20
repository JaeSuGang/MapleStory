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

	RenderComponent->SetSortingLayer(11);

	RenderComponent->SetBlendMode(1);

	RenderComponent->SetTextureByName("Resources\\Textures\\Fonts\\Damage\\" + std::to_string(Number) + ".png");

	RenderComponent->SetActorScaleByTextureSize();
}

void ADamageFont::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	Transform.Position.y += fDeltaTime * 50.0f;

	RemainedLifeTime -= fDeltaTime;

	if (RemainedLifeTime <= 0)
		this->Destroy();
}

void ADamageFont::SetNumber(int nNum)
{
	Number = nNum;
}
