#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"

#include "Actors/Screen/BP_LucidIntro.h"

BP_LucidIntro::BP_LucidIntro()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_LucidIntro::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->EnableMaterial();

	RenderComponent->SetTextureByName("Resources\\Textures\\Intro\\Lucid\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_DEBUG);

	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Intro\\Lucid", 33);

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void BP_LucidIntro::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	FTransform CameraTransform = GEngine->RenderSubsystem->GetCamera().Transform;
	Transform.Position.x = CameraTransform.Position.x;
	Transform.Position.y = CameraTransform.Position.y;

	RenderComponent->PlayAnimation(fDeltaTime);
}
