#pragma once
#include "Actions/GameplayAction.h"

class BP_ProneAction : public UGameplayAction
{
public:
	BP_ProneAction();

	void StartAction(AActor* Instigator) override;
};

