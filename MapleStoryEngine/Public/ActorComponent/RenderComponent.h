#pragma once
#include "ActorComponent.h"
#include "Math/Transform.h"

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* 생성자와 오버라이드 */
	void TickComponent(float fDeltaTime) override;

private:

};
