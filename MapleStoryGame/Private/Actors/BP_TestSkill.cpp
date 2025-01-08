#include "GamePch.h"
#include "actors/BP_TestSkill.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/Animation.h"

BP_TestSkill::BP_TestSkill()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_TestSkill::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->EnableMaterial();

	RenderComponent->SetMeshIDByName("Plane");
	RenderComponent->SetBlendMode(1);
	RenderComponent->SetTextureByName("Resources\\Textures\\13141005.screen.frames\\1.png");
	RenderComponent->SetActorScaleByTextureSize();
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Screen, "Resources\\Textures\\13141005.screen.frames", 60);
	RenderComponent->SetCurrentAnimation(EAnimationName::Screen);
}

void BP_TestSkill::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);
}
