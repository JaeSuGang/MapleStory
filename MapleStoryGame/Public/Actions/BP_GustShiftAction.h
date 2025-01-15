#pragma once
#include "Actions/GameplayAction.h"

class BP_GustShiftAction : public UGameplayAction
{
public:
	BP_GustShiftAction();
	void StartAction(AActor* Instigator) override;
};

