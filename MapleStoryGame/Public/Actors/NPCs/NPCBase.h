#pragma once
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

class URenderComponent;
class UPhysicsComponent;

class ANPCBase : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	ANPCBase();

	virtual void BeginPlay();

	virtual void Tick(float fDeltaTime);

public:
	void InitPhysics();

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;
};