#include "GamePch.h"
#include "Actors/Skills/BP_FairyTurn_0.h"
#include "RenderCore/RenderComponent.h"

BP_FairyTurn_0::BP_FairyTurn_0()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_FairyTurn_0::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->EnableMaterial();

	RenderComponent->SetMeshIDByName("Plane");
	RenderComponent->SetBlendMode(1);
	RenderComponent->SetTextureByName("Resources\\Textures\\13141004.effect.frames\\1.png");
	RenderComponent->SetActorScaleByTextureSize();
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\13141004.effect.frames", 60);
	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void BP_FairyTurn_0::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);

		Transform.Position = InstigatorTransform.Position;
		if (bIsLeftDirection)
			Transform.Position.x -= 200.0f;
		else
			Transform.Position.x += 200.0f;
	}
}
