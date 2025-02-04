#pragma once
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

class URenderComponent;
class UPhysicsComponent;
class UAttributeComponent;
class UActionComponent;
class AActor;

class BP_LucidBoss_0 : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	BP_LucidBoss_0();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	virtual void InitAttributes();

	virtual void InitTexture();

	virtual void InitAnimations();

	virtual void InitActions();

public:
	void SetFlower(AActor* _Flower);

	void SpawnBlades();

protected:

	void CheckAttack1Logic(float fDeltaTime);

	void InitPhysics();


public:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UAttributeComponent* AttributeComponent;

	UActionComponent* ActionComponent;

	string BossResourceName;

	AActor* Flower;

	float Attack1Timer;
};

