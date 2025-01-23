#pragma once
#include "Actions/GameplayAction.h"

class BP_IdleWhimAction : public UGameplayAction
{
public:
	BP_IdleWhimAction();

	void StartAction(AActor* Instigator) override;
};

