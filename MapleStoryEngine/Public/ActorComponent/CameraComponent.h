#pragma once
#include "ActorComponent/ActorComponent.h"

class UCameraComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API virtual void BeginPlay() override;

	ENGINE_API virtual void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetMainCamera(bool _Value);

protected:
	bool IsMainCamera;
};

