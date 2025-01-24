#include "GamePch.h"
#include "Actors/Skills/BP_IdleWhimAtom.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Actions/BP_TakeDamageAction.h"


BP_IdleWhimAtom::BP_IdleWhimAtom()
{
	LifeTime = 10.0f;
}

void BP_IdleWhimAtom::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (ElapsedTime > 0.2f && IsHit == false)
	{
		PhysicsComponent->FetchOverlappedHitboxActors(OverlappedActors);

		if (OverlappedActors.size() > 0)
		{
			IsHit = true;
			LifeTime = 1.0f;

			for (AActor* _Actor : OverlappedActors)
			{
				if (UActionComponent* _ActionComponent = _Actor->GetComponentByClass<UActionComponent>())
				{
					FDamageInfo _DamageInfo{};
					_DamageInfo.DamageRangeOffset = 0.1f;
					_DamageInfo.Damage = 12345678912.0f;
					_DamageInfo.TotalHitCount = 5;
					_DamageInfo.HitDelay = 0.1f;
					_DamageInfo.HitEffectPath = PATH_SKILL_HIT_1;

					_ActionComponent->StartActionByNameWithParameter(OverlappedActors[0], "Action.TakeDamage", &_DamageInfo);

					PhysicsComponent->SetVelocity({ 0.0f , 0.0f ,0.0f });
					break;
				}

			}
		}
	}

	if (IsHit)
	{
		RenderComponent->AddAlphaValue(-fDeltaTime);
	}

	if (!IsHit)
	{
		PhysicsComponent->AddForwardVelocity(-1000.0f * fDeltaTime);
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
