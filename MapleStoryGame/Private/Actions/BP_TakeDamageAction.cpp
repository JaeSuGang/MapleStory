#include "GamePch.h"
#include "Actions/BP_TakeDamageAction.h"
#include "Actor/Actor.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "World/World.h"
#include "Actors/DamageFont.h"

BP_TakeDamageAction::BP_TakeDamageAction()
{
	IsTickEnabled = true;

	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.TakeDamage");
}

void BP_TakeDamageAction::StartAction(AActor* Instigator, void* _ParameterStruct)
{
	FDamageInfo DamageInfo = *reinterpret_cast<FDamageInfo*>(_ParameterStruct);

	DamagesToApply.push_back(DamageInfo);
}

void BP_TakeDamageAction::Tick(float fDeltaTime)
{
	if (DamagesToApply.size() == 0)
		return;

	AActor* Instigator = ActionComponent->GetOwner();
	FVector3 HitPos = Instigator->GetTransform().Position;
	HitPos.y += Instigator->GetTransform().Scale.y / 4.0f;


	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent && AttributeComponent->HasAttributeExact("Value.Hp"))
	{
		for (FDamageInfo& Damage : DamagesToApply)
		{
			Damage.ElapsedTimeFromLastHit += fDeltaTime;

			if (Damage.ElapsedTimeFromLastHit > Damage.HitDelay)
			{
				Damage.ElapsedTimeFromLastHit -= Damage.HitDelay;
				Damage.CurrentHitCount += 1;

				AttributeComponent->AddAttributeValue("Value.Hp", -Damage.Damage);

				ADamageFont* Font = GetWorld()->SpawnActor<ADamageFont>();

				FVector3 AdjustedPos = HitPos;
				AdjustedPos.y += Damage.CurrentHitCount * 50.0f;

				Font->SetPosition(AdjustedPos);
				Font->SetNumber(std::rand() % 10);
			}
		}
	}


	DamagesToApply.erase(std::remove_if(DamagesToApply.begin(), DamagesToApply.end(), [](const FDamageInfo& Info) { return Info.CurrentHitCount >= Info.TotalHitCount; }), DamagesToApply.end());
}
