#pragma once
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

class URenderComponent;
class UPhysicsComponent;
class UAttributeComponent;
class UActionComponent;

class AMobBase : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	AMobBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	virtual void InitAttributes() = 0;

	virtual void InitTexture() = 0;

	virtual void InitAnimations() = 0;

	virtual void InitActions() = 0;

protected:
	void InitPhysics();


public:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UAttributeComponent* AttributeComponent;

	UActionComponent* ActionComponent;
};

