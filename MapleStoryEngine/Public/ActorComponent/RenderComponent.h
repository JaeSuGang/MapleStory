#pragma once
#include "ActorComponent.h"
#include "Math/Transform.h"

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* �����ڿ� �������̵� */
	void TickComponent(float fDeltaTime) override;

private:

};
