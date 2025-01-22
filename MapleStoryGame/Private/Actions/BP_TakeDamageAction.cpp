#include "GamePch.h"
#include "Actions/BP_TakeDamageAction.h"
#include "Actor/Actor.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "World/World.h"
#include "Actors/DamageFont.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/RandomManager.h"
#include "Actors/Skills/SkillBase.h"
#include "Actors/Skills/HitEffect.h"

BP_TakeDamageAction::BP_TakeDamageAction()
{
	IsTickEnabled = true;

	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.TakeDamage");

}

void BP_TakeDamageAction::StartAction(AActor* Instigator, void* _ParameterStruct)
{
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();

	if (!AttributeComponent->HasAttributeExact("Value.Hp") || AttributeComponent->GetAttributeValue("Value.Hp") <= 0.0f)
		return;

	FDamageInfo DamageInfo = *reinterpret_cast<FDamageInfo*>(_ParameterStruct);

	DamagesToApply.push_back(DamageInfo);
}

void BP_TakeDamageAction::Tick(float fDeltaTime)
{
	AActor* Instigator = ActionComponent->GetOwner();
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();

	if (DamagesToApply.size() == 0)
	{
		if (RenderComponent->GetCurrentAnimation() != EAnimationName::Die && AttributeComponent->GetAttributeValue("Value.Hp") <= 0.0f)
			RenderComponent->SetCurrentAnimation(EAnimationName::Die);

		return;
	}

	FVector3 HitPos = Instigator->GetTransform().Position;

	if (AttributeComponent && AttributeComponent->HasAttributeExact("Value.Hp"))
	{
		for (FDamageInfo& Damage : DamagesToApply)
		{
			Damage.ElapsedTimeFromLastHit += fDeltaTime;

			if (Damage.ElapsedTimeFromLastHit > Damage.HitDelay)
			{
				Damage.ElapsedTimeFromLastHit -= Damage.HitDelay;
				Damage.CurrentHitCount += 1;

				float FinalDamage = GEngine->RandomManager->GenerateRandomFloatValue(Damage.Damage * (1 - Damage.DamageRangeOffset), Damage.Damage * (1 + Damage.DamageRangeOffset));

				AttributeComponent->AddAttributeValue("Value.Hp", -1.0f * FinalDamage);
				RenderComponent->SetCurrentAnimation(EAnimationName::Hit);

				FVector3 PosToApply = HitPos;
				PosToApply.y += 50.0f * (Damage.CurrentHitCount);

				this->SpawnDamageFont(PosToApply, FinalDamage);
				this->SpawnHitEffect(HitPos, Damage);
			}
		}
	}


	DamagesToApply.erase(std::remove_if(DamagesToApply.begin(), DamagesToApply.end(), [](const FDamageInfo& Info) { return Info.CurrentHitCount >= Info.TotalHitCount; }), DamagesToApply.end());
}

void BP_TakeDamageAction::SpawnDamageFont(FVector3 Pos, float Damage)
{
	Pos.x += std::rand() % 30 - 15;

	long long nTemp = (long long)Damage;
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

void BP_TakeDamageAction::SpawnHitEffect(FVector3 Pos, FDamageInfo& Damage)
{
	Pos.x += std::rand() % 80 - 40;
	Pos.y += std::rand() % 80 - 40;

	AHitEffect* HitEffect = GetWorld()->SpawnActor<AHitEffect>();
	HitEffect->SetAnimation(Damage.HitEffectPath);
	HitEffect->SetPosition(Pos);
}
