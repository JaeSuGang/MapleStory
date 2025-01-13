#pragma once
#include "Actions/GameplayAction.h"

class BP_MoveAction : public UGameplayAction
{
public:
	BP_MoveAction();

	void StartAction(AActor* Instigator) override;


};

