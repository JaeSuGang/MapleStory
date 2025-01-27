#include "GamePch.h"
#include "Actors/Skills/BP_IdleWhimEffect.h"
#include "Actors/Skills/BP_IdleWhimAtom.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"

BP_IdleWhimEffect::BP_IdleWhimEffect()
{
	HasSpawndWhims = false;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_IdleWhimEffect::BeginPlay()
{
	Super::BeginPlay();

}

void BP_IdleWhimEffect::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (!HasSpawndWhims && ElapsedTime > 0.5f)
	{
		HasSpawndWhims = true;

		for (int i = 0; i < 10; i++)
		{
			FTransform SpawnTransform{};
			SpawnTransform.Position = Transform.Position;
			SpawnTransform.Position.x += GEngine->RandomManager->GenerateRandomFloatValue(-30.0f, 30.0f);
			SpawnTransform.Position.y += GEngine->RandomManager->GenerateRandomFloatValue(-30.0f, 30.0f);
			SpawnTransform.Rotation.z = GEngine->RandomManager->GenerateRandomFloatValue(0.0f, 360.0f);

			BP_IdleWhimAtom* Atom = GetWorld()->SpawnActor<BP_IdleWhimAtom>();
			Atom->SetInstigator(Instigator);
			Atom->SetPosition(SpawnTransform.Position);
		}
	}
}

void BP_IdleWhimEffect::InitAttributes()
{
	Super::InitAttributes();
}

void BP_IdleWhimEffect::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\IdleWhim\\effect\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	RenderComponent->SetSortingLayer(RENDER_LAYER_BACK_SKILL);
}

void BP_IdleWhimEffect::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\IdleWhim\\effect", 60);
}
