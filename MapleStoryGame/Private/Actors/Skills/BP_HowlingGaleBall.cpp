#include "GamePch.h"
#include "Math/Math.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Attributes/AttributeComponent.h"

#include "Actions/BP_TakeDamageAction.h"
#include "Actors/Skills/BP_HowlingGaleBall.h"


BP_HowlingGaleBall::BP_HowlingGaleBall()
{
	LifeTime = 10.0f;

	XVelocity = 200.0f;
}

void BP_HowlingGaleBall::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (RenderComponent->GetCurrentAnimation() == EAnimationName::Revive && RenderComponent->GetHasPassedLastFrame())
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
	}

	if (DamageCooldown <= 0.0f)
	{
		TempActorsVector.clear();
		PhysicsComponent->FetchOverlappedHitboxActors(TempActorsVector);

		if (TempActorsVector.size() > 0)
		{
			DamageCooldown = 0.15f;

			for (AActor* _Actor : TempActorsVector)
			{
				if (UActionComponent* _ActionComponent = _Actor->GetComponentByClass<UActionComponent>())
				{
					if (!_ActionComponent->HasAction("Action.TakeDamage"))
						continue;

					FDamageInfo _DamageInfo{};
					_DamageInfo.DamageRangeOffset = 0.1f;
					_DamageInfo.Damage = 15.60f * Instigator->GetComponentByClass<UAttributeComponent>()->GetAttributeValue("Value.Damage");
					_DamageInfo.TotalHitCount = 3;
					_DamageInfo.HitDelay = 0.1f;
					_DamageInfo.HitEffectPath = PATH_SKILL_HIT_2;

					for (AActor* _Target : TempActorsVector)
						_ActionComponent->StartActionByNameWithParameter(_Target, "Action.TakeDamage", &_DamageInfo);

					PhysicsComponent->SetVelocity({ 0.0f , 0.0f ,0.0f });
					break;
				}

			}
		}

	}

	else
	{
		DamageCooldown -= fDeltaTime;
	}

	if (FindTargetCooldown <= 0.0f)
	{
		FindTargetCooldown = 0.5f;

		FindTarget(2000.0f);
		shared_ptr<AActor> _TargetMonster = Target.lock();
		if (_TargetMonster.get())
		{
			FTransform _TargetTransform = _TargetMonster->GetTransform();

			if (Transform.Position.x > _TargetTransform.Position.x)
				XVelocity = -200.0f;

			else
				XVelocity = 200.0f;
		}
	}

	FindTargetCooldown -= fDeltaTime;
	PhysicsComponent->SetXVelocity(XVelocity);
}

void BP_HowlingGaleBall::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetCurrentAnimation(EAnimationName::Revive);

	FindTarget(2000.0f);
}

void BP_HowlingGaleBall::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\HowlingGale\\ball\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_HowlingGaleBall::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Revive, "Resources\\Textures\\Skills\\HowlingGale\\ballRevive", 120);

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\HowlingGale\\ball", 120);
}

void BP_HowlingGaleBall::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeMobFootCollider(Transform.Scale.y * -0.46f);
}
