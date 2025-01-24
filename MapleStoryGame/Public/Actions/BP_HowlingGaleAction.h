#pragma once
#include "Actions/GameplayAction.h"

class BP_HowlingGaleAction : public UGameplayAction
{
public:
	BP_HowlingGaleAction();

	void StartAction(AActor* Instigator) override;
};

