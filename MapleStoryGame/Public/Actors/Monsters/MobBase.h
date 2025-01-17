#pragma once
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

class URenderComponent;
class UPhysicsComponent;
class UAttributeComponent;

class AMobBase : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	AMobBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	virtual void SetAttributes() = 0;

	virtual void SetTexture() = 0;

public:

protected:
	void InitPhysics();


public:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UAttributeComponent* AttributeComponent;
};

