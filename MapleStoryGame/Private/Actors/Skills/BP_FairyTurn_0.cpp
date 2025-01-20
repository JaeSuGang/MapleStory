#include "GamePch.h"
#include "Actors/Skills/BP_FairyTurn_0.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"

BP_FairyTurn_0::BP_FairyTurn_0()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_FairyTurn_0::BeginPlay()
{
	Super::BeginPlay();

	this->SetPositionRelativeToInstigator(200.0f, 0.0f);



}

void BP_FairyTurn_0::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->SetPositionRelativeToInstigator(200.0f, 0.0f);
}

void BP_FairyTurn_0::InitAttributes()
{
	Super::InitAttributes();
}

void BP_FairyTurn_0::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\13141004.effect.frames\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_FairyTurn_0::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\13141004.effect.frames", 60);
}
