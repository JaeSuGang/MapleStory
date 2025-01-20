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

				AttributeComponent->AddAttributeValue("Value.Hp", -1.0f * Damage.Damage);

				FVector3 PosToApply = HitPos;
				PosToApply.y += 50.0f * (Damage.CurrentHitCount - 1);

				this->SpawnDamageFont(PosToApply, (int)Damage.Damage);
			}
		}
	}


	DamagesToApply.erase(std::remove_if(DamagesToApply.begin(), DamagesToApply.end(), [](const FDamageInfo& Info) { return Info.CurrentHitCount >= Info.TotalHitCount; }), DamagesToApply.end());
}

void BP_TakeDamageAction::SpawnDamageFont(FVector3 Pos, unsigned int nDamage)
{
	unsigned int nTemp = nDamage;
	vector<int> Numbers;

	while (nTemp)
	{
		if (Numbers.size() == 4)
			Numbers.push_back(10);

		else if (Numbers.size() == 9)
			Numbers.push_back(11);

		Numbers.push_back(nTemp % 10);
		nTemp = nTemp / 10;
	}

	int nSize = (int)Numbers.size();
	for (int i = 0; i < nSize; i++)
	{
		ADamageFont* Font = GetWorld()->SpawnActor<ADamageFont>();
		FVector3 PosToApply = Pos;
		PosToApply.x += ((float)nSize / 2.0f - i) * 30.0f;
		Font->SetNumber(Numbers[i]);
		Font->SetPosition(PosToApply);
	}
}
