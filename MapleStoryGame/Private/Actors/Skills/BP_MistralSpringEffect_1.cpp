#include "GamePch.h"
#include "Actors/Skills/BP_MistralSpringEffect_1.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"

BP_MistralSpringEffect_1::BP_MistralSpringEffect_1()
{
	IsLoopingSkill = true;

	IsScreenSkill = true;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_MistralSpringEffect_1::BeginPlay()
{
	Super::BeginPlay();

}

void BP_MistralSpringEffect_1::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	ElapsedTime += fDeltaTime;

	if (ElapsedTime > 20.0f)
		this->Destroy();

	else if (ElapsedTime > 18.0f)
		RenderComponent->AddAlphaValue(-0.5f * fDeltaTime);
}

void BP_MistralSpringEffect_1::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\customEffect1\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_BACK_SKILL);
}

void BP_MistralSpringEffect_1::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\customEffect1", 60);
}
