#include "GamePch.h"
#include "Actions/BP_TakeDamageAction.h"
#include "Actor/Actor.h"
#include "Attributes/AttributeComponent.h"

BP_TakeDamageAction::BP_TakeDamageAction()
{
	IsTickEnabled = true;
}

void BP_TakeDamageAction::StartAction(AActor* Instigator, void* _ParameterStruct)
{
	FDamageInfo DamageInfo = *reinterpret_cast<FDamageInfo*>(_ParameterStruct);

	DamagesToApply.push_back(DamageInfo);

	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->HasAttributeExact("Value.Hp"))
		{

		}
	}
}

void BP_TakeDamageAction::Tick(float fDeltaTime)
{
	for (FDamageInfo& Damage : DamagesToApply)
	{
		if (Damage.ElapsedTimeFromLastHit > Damage.HitDelay)
		{

		}
	}

	DamagesToApply.erase(std::remove_if(DamagesToApply.begin(), DamagesToApply.end(), [](const FDamageInfo& Info) { return Info.HitCountLeft <= 0; }), DamagesToApply.end());
}
