#include "GamePch.h"
#include "Actors/Skills/BP_IdleWhimAtom.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"


BP_IdleWhimAtom::BP_IdleWhimAtom()
{
	LifeTime = 10.0f;

	ContactShapes.reserve(20);
}

void BP_IdleWhimAtom::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (ElapsedTime > 0.2f)
	{
		if (PhysicsComponent->GetSensorOverlappedShapes(ContactShapes))
		{
			if (IsHit == false)
			{
				IsHit = true;
				LifeTime = 1.0f;

				for (b2ShapeId& ShapeId : ContactShapes)
				{
					GEngine->physics
				}
			}

			RenderComponent->AddAlphaValue(-fDeltaTime);
			PhysicsComponent->SetVelocity({ 0.0f, 0.0f, 0.0f });
		}
		else
		{


			PhysicsComponent->AddForwardVelocity(-1000.0f * fDeltaTime);
		}

	}
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
