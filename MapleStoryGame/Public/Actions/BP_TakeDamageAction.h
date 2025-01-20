#pragma once
#include "Actions/GameplayAction.h"
#include "Math/Vector3.h"

struct FDamageInfo
{
	unsigned int Damage;
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
	void SpawnDamageFont(FVector3 Pos, unsigned int nDamage);

protected:
	vector<FDamageInfo> DamagesToApply;
};

