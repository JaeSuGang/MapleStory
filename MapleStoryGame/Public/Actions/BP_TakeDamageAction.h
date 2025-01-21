#pragma once
#include "Actions/GameplayAction.h"
#include "Math/Vector3.h"

class UAttributeComponent;

struct FDamageInfo
{
	float Damage;
	float DamageRangeOffset; /* (1 - n) ~ (1 + n) ÀÇ °ªÁß ·£´ý */
	float HitDelay;
	float ElapsedTimeFromLastHit;
	int TotalHitCount;
	int CurrentHitCount;
};

class BP_TakeDamageAction : public UGameplayAction
{
public:
	BP_TakeDamageAction();

	void StartAction(AActor* Instigator, void* _ParameterStruct) override;

	void Tick(float fDeltaTime) override;

protected:
	void SpawnDamageFont(FVector3 Pos, float fDamage);

protected:
	vector<FDamageInfo> DamagesToApply;
};

