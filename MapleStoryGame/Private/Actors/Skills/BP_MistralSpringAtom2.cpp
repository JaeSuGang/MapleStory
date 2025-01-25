#include "GamePch.h"
#include "Math/Math.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Attributes/AttributeComponent.h"

#include "Actions/BP_TakeDamageAction.h"
#include "Actors/Skills/BP_MistralSpringAtom2.h"


BP_MistralSpringAtom2::BP_MistralSpringAtom2()
{
	LifeTime = 4.0f;
}

void BP_MistralSpringAtom2::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (ElapsedTime > 0.2f && !IsHit)
	{
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
				break;
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

		if (_TargetMonster.get() && _TargetMonster->GetComponentByClass<UAttributeComponent>()->HasAttributeExact("Status.Hitable"))
		{
			FTransform _TargetTransform = _TargetMonster->GetTransform();

			float _AngleDiff = GetZAngle(Transform.Position, _TargetTransform.Position, Transform.Rotation);

			_AngleDiff = NormalizeDirectionAngle(_AngleDiff + 180.0f);

			float _AngleToApply = _AngleDiff * 5.0f * fDeltaTime;

			AddZRotation(_AngleToApply);

			PhysicsComponent->SetForwardVelocity(-1200.0f);
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

void BP_MistralSpringAtom2::BeginPlay()
{
	Super::BeginPlay();

	FindTarget(3000.0f);
}

void BP_MistralSpringAtom2::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\MistralSpring\\atom2\\idle\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_MistralSpringAtom2::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Revive, "Resources\\Textures\\Skills\\MistralSpring\\atom2\\revive", 60);

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\atom2\\idle", 120);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Skills\\MistralSpring\\atom2\\die", 60);
}

void BP_MistralSpringAtom2::InitPhysics()
{
	Super::InitPhysics();

	SetRotation({ 0.0f, 0.0f, -90.0f });
}
