#pragma once
#include "Actions/GameplayAction.h"

class BP_MoveRightAction : public UGameplayAction
{
public:
	BP_MoveRightAction();

	void StartAction(AActor* Instigator) override;


};

