#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;
class UActionComponent;
class UAttributeComponent;
class UCameraComponent;

class ACharacterBase : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	ACharacterBase();

	~ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	void LateTick(float fDeltaTime) override;

	virtual void InitActions();

	virtual void InitAnimations();

	virtual void InitTextures();

	virtual void InitPhysics();

	virtual void SetPosition(FVector3 _Position);

public:
	virtual void BindKeys();

protected:
	void DecideAnimation();

	void CheckFalling();


protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UActionComponent* ActionComponent;

	UAttributeComponent* AttributeComponent;

	UCameraComponent* CameraComponent;
};

