#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;

class ACharacterBase : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;
};

