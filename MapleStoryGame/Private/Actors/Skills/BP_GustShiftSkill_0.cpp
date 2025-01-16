#include "GamePch.h"
#include "Actors/Skills/BP_GustShiftSkill_0.h"
#include "RenderCore/RenderComponent.h"

BP_GustShiftSkill_0::BP_GustShiftSkill_0()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_GustShiftSkill_0::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->EnableMaterial();

	RenderComponent->SetMeshIDByName("Plane");
	RenderComponent->SetBlendMode(1);
	RenderComponent->SetTextureByName("Resources\\Textures\\13001024.effect.frames\\1.png");
	RenderComponent->SetActorScaleByTextureSize();
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\13001024.effect.frames", 60);
	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void BP_GustShiftSkill_0::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);
		bool bIsUpDirection = (int)Transform.Rotation.z % 360 == 270;

		Transform.Position = InstigatorTransform.Position;

		if (bIsUpDirection)
			Transform.Position.y -= 90.0f;
		else
		{
			Transform.Rotation = InstigatorTransform.Rotation;
			Transform.Position.y -= 10.0f;
			if (bIsLeftDirection)
				Transform.Position.x += 90.0f;

			else
				Transform.Position.x -= 90.0f;
		}
	}
}
