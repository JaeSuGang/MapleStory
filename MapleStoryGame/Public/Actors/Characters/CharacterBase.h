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
	/* �����ڿ� �������̵� */
	ACharacterBase();

	~ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	void LateTick(float fDeltaTime) override;

	virtual void InitActions();

	virtual void InitAttributes();

	virtual void InitAnimations();

	virtual void InitTextures();

	virtual void InitPhysics();

	virtual void SetPosition(FVector3 _Position);

	virtual void BindKeys();
public:
	float GetDamage() const;

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

