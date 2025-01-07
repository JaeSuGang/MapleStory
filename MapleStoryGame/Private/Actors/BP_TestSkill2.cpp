#include "GamePch.h"
#include "actors/BP_TestSkill2.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/Animation.h"

BP_TestSkill2::BP_TestSkill2()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_TestSkill2::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->EnableMaterial();

	RenderComponent->SetMeshIDByName("Plane");
	RenderComponent->SetBlendMode(1);
	RenderComponent->SetTextureByName("Resources\\Textures\\13141500.screen.frames\\0.png");
	RenderComponent->SetActorScaleByTextureSize();
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Screen, "Resources\\Textures\\13141500.screen.frames", 60);
	RenderComponent->SetCurrentAnimation(EAnimationName::Screen);
}

void BP_TestSkill2::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);
}
