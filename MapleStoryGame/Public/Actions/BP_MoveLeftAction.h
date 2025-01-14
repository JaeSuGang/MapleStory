#pragma once
#include "Actions/GameplayAction.h"

class BP_MoveLeftAction : public UGameplayAction
{
public:
	BP_MoveLeftAction();

	void StartAction(AActor* Instigator) override;
};

