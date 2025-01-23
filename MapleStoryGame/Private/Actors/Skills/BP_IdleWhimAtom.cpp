#include "GamePch.h"
#include "Actors/Skills/BP_IdleWhimAtom.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"


void BP_IdleWhimAtom::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (ElapsedTime > 0.2f)
		PhysicsComponent->AddForwardVelocity(-1000.0f * fDeltaTime);
}

void BP_IdleWhimAtom::BeginPlay()
{
	Super::BeginPlay();
}

void BP_IdleWhimAtom::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\IdleWhim\\atom\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_IdleWhimAtom::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\IdleWhim\\atom", 90);	
}

void BP_IdleWhimAtom::InitPhysics()
{
	Super::InitPhysics();

	SetRotation({ 0.0f, 0.0f, GEngine->RandomManager->GenerateRandomFloatValue(0.0f, 360.0f) });
}
