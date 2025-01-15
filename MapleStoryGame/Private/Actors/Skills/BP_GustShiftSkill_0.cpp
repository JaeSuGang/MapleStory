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

}
