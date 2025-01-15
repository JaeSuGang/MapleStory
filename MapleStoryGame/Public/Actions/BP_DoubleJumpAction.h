#pragma once
#include "Actions/GameplayAction.h"

class BP_DoubleJumpAction : public UGameplayAction
{
public:
	BP_DoubleJumpAction();

	void StartAction(AActor* Instigator) override;
};

