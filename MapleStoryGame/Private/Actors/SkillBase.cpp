#include "GamePch.h"
#include "Actors/SkillBase.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"

ASkillBase::ASkillBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void ASkillBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetSortingLayer(10);
	RenderComponent->SetBlendMode(1);
}

void ASkillBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (IsScreenSkill)
	{
		FTransform CameraTransform = GEngine->RenderSubsystem->GetCamera().Transform;
		Transform.Position.x = CameraTransform.Position.x;
		Transform.Position.y = CameraTransform.Position.y;
	}
}
