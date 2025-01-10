#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;

class AFootholdBase : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	AFootholdBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	void InitializeValues(float x1, float y1, float x2, float y2);

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	b2BodyId BodyID;
};

