#pragma once
#include "Actions/GameplayAction.h"

class BP_FairyTurnAction : public UGameplayAction
{
public:
	BP_FairyTurnAction();

	void StartAction(AActor* Instigator) override;
};

