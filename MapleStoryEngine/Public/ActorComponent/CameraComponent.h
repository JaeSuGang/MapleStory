#pragma once
#include "ActorComponent/ActorComponent.h"

class UCameraComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* �����ڿ� �������̵� */
	ENGINE_API virtual void BeginPlay() override;

	ENGINE_API virtual void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetMainCamera(bool _Value);

protected:
	bool IsMainCamera;
};

