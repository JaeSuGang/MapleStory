#pragma once
#include "Actions/GameplayAction.h"

class BP_SongOfHeavenEffect;

class BP_SongOfHeavenAction : public UGameplayAction
{
	typedef UGameplayAction Super;

public:
	BP_SongOfHeavenAction();

	void StartAction(AActor* Instigator) override;

	void Tick(float fDeltaTime) override;

protected:
	weak_ptr<BP_SongOfHeavenEffect> Effect;

	float Cooldown;
};

