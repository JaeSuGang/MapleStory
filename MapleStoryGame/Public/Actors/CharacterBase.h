#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;
class UActionComponent;

class ACharacterBase : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	void BindKeys();

protected:
	void InitActions();

	void InitTextureAndPhysics();

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UActionComponent* ActionComponent;
};

