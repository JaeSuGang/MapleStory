#pragma once
#include "ActorComponent/CameraComponent.h"

class UMapleCameraComponent : public UCameraComponent
{
	typedef UCameraComponent Super;

public:
	void TickComponent(float fDeltaTime) override;
};

