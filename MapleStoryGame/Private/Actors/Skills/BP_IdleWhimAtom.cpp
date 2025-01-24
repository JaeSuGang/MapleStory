#include "GamePch.h"
#include "Math/Math.h"
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
		PhysicsComponent->FetchOverlappedHitboxActors(TempActorsVector);

		if (TempActorsVector.size() > 0)
		{
			IsHit = true;
			LifeTime = 1.0f;

			for (AActor* _Actor : TempActorsVector)
			{
				if (UActionComponent* _ActionComponent = _Actor->GetComponentByClass<UActionComponent>())
				{
					FDamageInfo _DamageInfo{};
					_DamageInfo.DamageRangeOffset = 0.1f;
					_DamageInfo.Damage = 12345678912.0f;
					_DamageInfo.TotalHitCount = 5;
					_DamageInfo.HitDelay = 0.1f;
					_DamageInfo.HitEffectPath = PATH_SKILL_HIT_1;

					_ActionComponent->StartActionByNameWithParameter(TempActorsVector[0], "Action.TakeDamage", &_DamageInfo);

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
		shared_ptr<AActor> _TargetMonster = Target.lock();

		if (_TargetMonster.get())
		{
			FTransform _TargetTransform = _TargetMonster->GetTransform();
			
			float _AngleDiff = GetZAngle(Transform.Position, _TargetTransform.Position);

			float _AngleToApply = _AngleDiff * 30.0f * fDeltaTime;
		
			AddZRotation(_AngleToApply);
		}

		else
		{
			FindTargetCooldown -= fDeltaTime;

			if (FindTargetCooldown < 0)
			{
				FindTargetCooldown = 1.0f;
				FindTarget(1000.0f);
			}
		}

		PhysicsComponent->SetForwardVelocity(-800.0f);
	}
}

void BP_IdleWhimAtom::BeginPlay()
{
	Super::BeginPlay();

	FindTarget(1000.0f);
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
