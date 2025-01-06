#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;

class BP_TestFloor : public AActor
{
	typedef AActor Super;

public:
	BP_TestFloor();
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;
};

