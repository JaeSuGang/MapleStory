#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "World/World.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"

#include "Actors/Skills/BP_MistralSpringSummon.h"
#include "Actors/Skills/BP_MistralSpringAtom0.h"
#include "Actors/Skills/BP_MistralSpringAtom1.h"
#include "Actors/Skills/BP_MistralSpringAtom2.h"

BP_MistralSpringSummon::BP_MistralSpringSummon()
{
	SummonTime = 0.0f;

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

	SummonTime -= fDeltaTime;

	if (SummonTime <= 0.0f)
	{
		SummonTime = 3.0f;
		FTransform _Transform = Transform;
		for (int i = 0; i < 15; i++)
		{
			BP_MistralSpringAtom0* _Atom0 = GetWorld()->SpawnActor<BP_MistralSpringAtom0>();
			_Atom0->SetInstigator(Instigator);
			_Atom0->SetRandomPosition(_Transform.Position, 200.0f);
		}

		for (int i = 0; i < 5; i++)
		{
			BP_MistralSpringAtom1* _Atom1 = GetWorld()->SpawnActor<BP_MistralSpringAtom1>();
			_Atom1->SetInstigator(Instigator);
			_Atom1->SetRandomPosition(_Transform.Position, 200.0f);
		}

		for (int i = 0; i < 3; i++)
		{
			BP_MistralSpringAtom2* _Atom2 = GetWorld()->SpawnActor<BP_MistralSpringAtom2>();
			_Atom2->SetInstigator(Instigator);
			_Atom2->SetRandomPosition(_Transform.Position, 200.0f);
		}
	}


	if (ElapsedTime > 30.0f)
		this->Destroy();

	else if (ElapsedTime > 28.0f)
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
