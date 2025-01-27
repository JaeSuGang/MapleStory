#include "GamePch.h"
#include "Math/Math.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Actor/Actor.h"

#include "Actions/BP_TakeDamageAction.h"
#include "Actors/Skills/BP_SongOfHeavenAtom.h"


BP_SongOfHeavenAtom::BP_SongOfHeavenAtom()
{
	LifeTime = 1.0f;
}

void BP_SongOfHeavenAtom::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (ElapsedTime > 0.2f && IsHit == false)
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
				_DamageInfo.Damage = 11.55f * Instigator->GetComponentByClass<UAttributeComponent>()->GetAttributeValue("Value.Damage");
				_DamageInfo.TotalHitCount = 1;
				_DamageInfo.HitDelay = 0.1f;
				_DamageInfo.HitEffectPath = PATH_SKILL_HIT_1;

				_ActionComponent->StartActionByNameWithParameter(_Actor, "Action.TakeDamage", &_DamageInfo);

				PhysicsComponent->SetVelocity({ 0.0f , 0.0f ,0.0f });
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

			_AngleDiff = _AngleDiff * 10.0f * fDeltaTime;

			AddZRotation(_AngleDiff);
		}

		PhysicsComponent->SetForwardVelocity(-600.0f);
	}
}
	
void BP_SongOfHeavenAtom::BeginPlay()
{
	Super::BeginPlay();

	FTransform TransformToApply = Instigator->GetTransform();

	if (TransformToApply.Rotation.y == 180.0f)
	{
		TransformToApply.Position.x += 70.0f;
		TransformToApply.Position.y -= 10.0f;
		TransformToApply.Rotation = { 0.0f, 0.0f, 180.0f };
	}
	else
	{
		TransformToApply.Position.x -= 70.0f;
		TransformToApply.Position.y -= 10.0f;
		TransformToApply.Rotation = { 0.0f, 0.0f, 0.0f };
	}

	SetPosition(TransformToApply.Position);
	SetRotation(TransformToApply.Rotation);
	Transform.Position = TransformToApply.Position;
	Transform.Rotation= TransformToApply.Rotation;

	FindTarget(500.0f);
}

void BP_SongOfHeavenAtom::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\SongOfHeaven\\atom\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_SongOfHeavenAtom::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\MistralSpring\\atom0\\idle", 60);
}

void BP_SongOfHeavenAtom::InitPhysics()
{
	Super::InitPhysics();
}
