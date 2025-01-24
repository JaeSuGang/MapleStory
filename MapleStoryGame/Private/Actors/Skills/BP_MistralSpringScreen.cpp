#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"

#include "Actors/Skills/BP_MistralSpringScreen.h"
#include "Actors/Skills/BP_MistralSpringEffect_0.h"
#include "Actors/Skills/BP_MistralSpringEffect_1.h"


BP_MistralSpringScreen::BP_MistralSpringScreen()
{
	IsScreenSkill = true;

	HasSpawnedSpecialEffect = false;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_MistralSpringScreen::BeginPlay()
{
	Super::BeginPlay();

}

void BP_MistralSpringScreen::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


	if (!HasSpawnedSpecialEffect && ElapsedTime > 4.0f)
	{
		HasSpawnedSpecialEffect = true;
		BP_MistralSpringEffect_0* Effect0 = GetWorld()->SpawnActor<BP_MistralSpringEffect_0>();
		BP_MistralSpringEffect_1* Effect1 = GetWorld()->SpawnActor<BP_MistralSpringEffect_1>();
	}
}

void BP_MistralSpringScreen::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\screen\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_FRONT_SKILL);
}

void BP_MistralSpringScreen::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\screen", 60);
}
