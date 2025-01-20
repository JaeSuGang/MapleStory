#include "GamePch.h"
#include "Actions/BP_TakeDamageAction.h"
#include "Actor/Actor.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"

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

	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent && AttributeComponent->HasAttributeExact("Value.Hp"))
	{
		for (FDamageInfo& Damage : DamagesToApply)
		{
			Damage.ElapsedTimeFromLastHit += fDeltaTime;

			if (Damage.ElapsedTimeFromLastHit > Damage.HitDelay)
			{
				Damage.ElapsedTimeFromLastHit -= Damage.HitDelay;
				Damage.HitCountLeft -= 1;

				AttributeComponent->AddAttributeValue("Value.Hp", -Damage.Damage);

			}
		}
	}


	DamagesToApply.erase(std::remove_if(DamagesToApply.begin(), DamagesToApply.end(), [](const FDamageInfo& Info) { return Info.HitCountLeft <= 0; }), DamagesToApply.end());
}
