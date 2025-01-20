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

	virtual void InitTexture();

	virtual void InitAnimations();

	virtual void InitActions();

protected:
	void SetResourcePath(string strPath);

	void InitPhysics();


public:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UAttributeComponent* AttributeComponent;

	UActionComponent* ActionComponent;

	string MobResourcePath;
};

