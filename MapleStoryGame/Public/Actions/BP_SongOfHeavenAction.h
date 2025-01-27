#pragma once
#include "Actions/GameplayAction.h"

class BP_SongOfHeavenAction : public UGameplayAction
{
	typedef UGameplayAction Super;

public:
	BP_SongOfHeavenAction();

	void StartAction(AActor* Instigator) override;
};

