#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;
class UActionComponent;

class ACharacterBase : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	ACharacterBase();

	~ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	void BindKeys();

protected:
	void CheckVelocity();

	void InitActions();

	void InitTextureAndPhysics();

	void InitAnimations();

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UActionComponent* ActionComponent;
};

