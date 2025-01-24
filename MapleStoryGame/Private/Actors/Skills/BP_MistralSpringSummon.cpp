#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "World/World.h"

#include "Actors/Skills/BP_MistralSpringSummon.h"

BP_MistralSpringSummon::BP_MistralSpringSummon()
{
	IsLoopingSkill = true;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_MistralSpringSummon::BeginPlay()
{
	Super::BeginPlay();

}

void BP_MistralSpringSummon::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


	if (ElapsedTime > 20.0f)
		this->Destroy();

	else if (ElapsedTime > 18.0f)
		RenderComponent->AddAlphaValue(-0.5f * fDeltaTime);
}

void BP_MistralSpringSummon::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\summon\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_BACK_SKILL);
}

void BP_MistralSpringSummon::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\summon", 90);
}
