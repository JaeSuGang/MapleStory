#pragma once
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

class URenderComponent;
class UPhysicsComponent;
class UAttributeComponent;
class UActionComponent;

class BP_LucidFlower : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	BP_LucidFlower();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	virtual void InitTexture();

	virtual void InitAnimations();

protected:
	void SetResourcePath(string strPath);


public:
	URenderComponent* RenderComponent;

	string ResourceName;
};

