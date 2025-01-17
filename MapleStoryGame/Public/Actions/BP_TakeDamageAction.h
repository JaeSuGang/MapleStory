#pragma once
#include "Actions/GameplayAction.h"

class BP_TakeDamageAction : public UGameplayAction
{
public:
	void StartAction(AActor* Instigator) override;

public:
	void TakeDamage(AActor* Instigator, float fDamage, int nDamageCount);
};

