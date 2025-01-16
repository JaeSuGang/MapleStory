#pragma once
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

class URenderComponent;
class UPhysicsComponent;

class AMobBase : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	AMobBase();

	virtual void BeginPlay() = 0;

	virtual void Tick(float fDeltaTime) = 0;

public:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;
};

