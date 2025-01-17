#include "GamePch.h"
#include "Actors/Skills/SkillBase.h"
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

	if (RenderComponent->GetHasPassedLastFrame())
	{
		this->Destroy();
		return;
	}

	if (IsScreenSkill)
	{
		FTransform CameraTransform = GEngine->RenderSubsystem->GetCamera().Transform;
		Transform.Position.x = CameraTransform.Position.x;
		Transform.Position.y = CameraTransform.Position.y;
	}

	RenderComponent->PlayAnimation(fDeltaTime);
}

void ASkillBase::SetInstigator(AActor* _Instigator)
{
	Instigator = _Instigator;
}

void ASkillBase::SetPositionRelativeToInstigator(float fLeft, float fUp)
{
	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);

		Transform.Position = InstigatorTransform.Position;
		if (bIsLeftDirection)
		{
			Transform.Position.x -= fLeft;
			Transform.Position.y += fUp;
		}
		else
		{
			Transform.Position.x += fLeft;
			Transform.Position.y += fUp;
		}
	}
}
