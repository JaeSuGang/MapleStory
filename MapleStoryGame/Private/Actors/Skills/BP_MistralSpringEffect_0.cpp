#include "GamePch.h"
#include "Actors/Skills/BP_MistralSpringEffect_0.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"

BP_MistralSpringEffect_0::BP_MistralSpringEffect_0()
{
	IsScreenSkill = true;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_MistralSpringEffect_0::BeginPlay()
{
	Super::BeginPlay();

}

void BP_MistralSpringEffect_0::Tick(float fDeltaTime)
{
	AActor::Tick(fDeltaTime);

	ElapsedTime += fDeltaTime;

	FTransform CameraTransform = GEngine->RenderSubsystem->GetCamera().Transform;
	Transform.Position.x = CameraTransform.Position.x;
	Transform.Position.y = CameraTransform.Position.y;

	RenderComponent->PlayAnimation(fDeltaTime);

	if (ElapsedTime > 20.0f)
		this->Destroy();

	else if (ElapsedTime > 18.0f)
		RenderComponent->AddAlphaValue(-0.5f * fDeltaTime);
}

void BP_MistralSpringEffect_0::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\customEffect0\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_BEHIND_FOOTHOLD);
}

void BP_MistralSpringEffect_0::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\customEffect0", 60);
}
