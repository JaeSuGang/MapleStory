#pragma once
#include "Actions/GameplayAction.h"

class BP_MistralSpringAction : public UGameplayAction
{
public:
	BP_MistralSpringAction();

	void StartAction(AActor* Instigator) override;
};

