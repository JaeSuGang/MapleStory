#include "GamePch.h"
#include "Actors/BP_OrangeMushroom.h"

void BP_OrangeMushroom::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetTextureByName("Resources\\Textures\\9000404.img.stand.0.png");
	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeAsMobFoot(3.0f, Transform.Scale.y * -0.49f, MOB_COLLISION_FLAG);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\9000404.img.stand.frames", 180);
	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);

	
}

void BP_OrangeMushroom::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);
}
