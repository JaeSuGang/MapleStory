#pragma once
#include "Actions/GameplayAction.h"

class BP_JumpAction : public UGameplayAction
{
public:
	BP_JumpAction();

	void StartAction(AActor* Instigator) override;
};

