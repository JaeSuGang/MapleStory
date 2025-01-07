#include "GamePch.h"
#include "Actors/BP_OrangeMushroom.h"

void BP_OrangeMushroom::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetTextureByName("Resources\\Textures\\9000404.img.stand.0.png");
	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeAsDynamicRigidBody(Transform.Scale.x, Transform.Scale.y, MOB_COLLISION_FLAG);

	/* 애니메이션 추가 */
	RenderComponent->EnableAnimation();
	RenderComponent->AddAnimationByFolder(EAnimationName::Stand, "Resources\\Textures\\9000404.img.stand.frames", 180);
	RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
}

void BP_OrangeMushroom::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);
}
