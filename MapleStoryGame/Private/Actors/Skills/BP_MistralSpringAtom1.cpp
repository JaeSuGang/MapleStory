#include "GamePch.h"
#include "Math/Math.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Attributes/AttributeComponent.h"

#include "Actions/BP_TakeDamageAction.h"
#include "Actors/Skills/BP_MistralSpringAtom1.h"


BP_MistralSpringAtom1::BP_MistralSpringAtom1()
{
	HasShot = false;

	LifeTime = 4.0f;
}

void BP_MistralSpringAtom1::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (ElapsedTime > 0.2f && IsHit == false)
	{
		if (!HasShot)
		{
			RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
			HasShot = true;
		}

		PhysicsComponent->FetchOverlappedHitboxActors(TempActorsVector);

		if (TempActorsVector.size() > 0)
		{
			for (AActor* _Actor : TempActorsVector)
			{
				UAttributeComponent* _AttributeComponent = _Actor->GetComponentByClass<UAttributeComponent>();
				UActionComponent* _ActionComponent = _Actor->GetComponentByClass<UActionComponent>();
				if (!_AttributeComponent || !_AttributeComponent->HasAttributeExact("Status.Hitable"))
					continue;

				if (!_ActionComponent || !_ActionComponent->HasAction("Action.TakeDamage"))
					continue;

				IsHit = true;
				LifeTime = 1.0f;

				FDamageInfo _DamageInfo{};
				_DamageInfo.DamageRangeOffset = 0.1f;
				_DamageInfo.Damage = 12345678912.0f;
				_DamageInfo.TotalHitCount = 5;
				_DamageInfo.HitDelay = 0.1f;
				_DamageInfo.HitEffectPath = PATH_SKILL_HIT_1;

				_ActionComponent->StartActionByNameWithParameter(_Actor, "Action.TakeDamage", &_DamageInfo);

				PhysicsComponent->SetVelocity({ 0.0f , 0.0f ,0.0f });

				RenderComponent->SetCurrentAnimation(EAnimationName::Die);
				break;
			}
		}
	}

	if (!IsHit)
	{
		shared_ptr<AActor> _TargetMonster = Target.lock();

		if (_TargetMonster.get() && _TargetMonster->GetComponentByClass<UAttributeComponent>()->HasAttributeExact("Status.Hitable"))
		{
			FTransform _TargetTransform = _TargetMonster->GetTransform();

			float _AngleDiff = GetZAngle(Transform.Position, _TargetTransform.Position, Transform.Rotation);

			_AngleDiff = NormalizeDirectionAngle(_AngleDiff + 180.0f);

			if (ElapsedTime > 0.2f)
			{
				float _AccelVel = -1000.0f * (ElapsedTime > 1.0f ? 1.0f : ElapsedTime);
				float _AccelRot = 10.0f * (ElapsedTime > 1.0f ? 1.0f : ElapsedTime);
				float _AngleToApply = _AngleDiff * _AccelRot * fDeltaTime;
				AddZRotation(_AngleToApply);
				PhysicsComponent->SetForwardVelocity(-800.0f + _AccelVel);
			}
		}

		else
		{
			FindTargetCooldown -= fDeltaTime;

			if (FindTargetCooldown < 0)
			{
				FindTargetCooldown = 1.0f;
				FindTarget(3000.0f);
			}
		}

	}
}

void BP_MistralSpringAtom1::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetCurrentAnimation(EAnimationName::Revive);

	SetRandomRotation();

	FindTarget(3000.0f);
}

void BP_MistralSpringAtom1::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\atom1\\idle\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_MistralSpringAtom1::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Revive, "Resources\\Textures\\Skills\\MistralSpring\\atom1\\revive", 60);

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\atom1\\idle", 60);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Skills\\MistralSpring\\atom1\\die", 60);
}

void BP_MistralSpringAtom1::InitPhysics()
{
	Super::InitPhysics();

	SetRotation({ 0.0f, 0.0f, -90.0f });
}
