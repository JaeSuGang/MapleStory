#pragma once
#include "Actions/GameplayAction.h"

struct FDamageInfo
{
	float Damage;
	float HitDelay;
	float ElapsedTimeFromLastHit;
	int HitCountLeft;
};

class BP_TakeDamageAction : public UGameplayAction
{
public:
	BP_TakeDamageAction();

	void StartAction(AActor* Instigator, void* _ParameterStruct) override;

	void Tick(float fDeltaTime) override;

protected:
	vector<FDamageInfo> DamagesToApply;
};

