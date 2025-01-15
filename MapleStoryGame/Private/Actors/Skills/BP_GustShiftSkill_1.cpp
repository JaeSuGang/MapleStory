#include "GamePch.h"
#include "Actors/Skills/BP_GustShiftSkill_1.h"
#include "RenderCore/RenderComponent.h"

BP_GustShiftSkill_1::BP_GustShiftActor_1()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_GustShiftSkill_1::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->EnableMaterial();

	RenderComponent->SetMeshIDByName("Plane");
	RenderComponent->SetBlendMode(1);
	RenderComponent->SetTextureByName("Resources\\Textures\\13001024.effect0.frames\\1.png");
	RenderComponent->SetActorScaleByTextureSize();
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\13001024.effect0.frames", 60);
	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void BP_GustShiftSkill_1::Tick(float fDeltaTime)
{

}
