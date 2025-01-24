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
#include "Actors/Skills/BP_MistralSpringSummon.h"


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
		BP_MistralSpringSummon* Summon = GetWorld()->SpawnActor<BP_MistralSpringSummon>();

		FVector3 _SummonPos = Instigator->GetTransform().Position;
		Summon->SetInstigator(Instigator);
		_SummonPos.y += 130.0f;
		Summon->SetPosition(_SummonPos);
	}
}

void BP_MistralSpringScreen::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\screen\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_HIT_EFFECT);
}

void BP_MistralSpringScreen::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\screen", 60);
}
