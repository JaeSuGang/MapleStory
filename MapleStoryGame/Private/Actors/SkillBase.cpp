#include "GamePch.h"
#include "Actors/SkillBase.h"
#include "RenderCore/RenderComponent.h"

ASkillBase::ASkillBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void ASkillBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetBlendMode(1);
}

void ASkillBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
