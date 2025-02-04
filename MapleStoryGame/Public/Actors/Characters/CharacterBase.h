#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;
class UActionComponent;
class UAttributeComponent;
class UCameraComponent;
class BP_HPWidget;

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

	virtual void InitAttributes();

	virtual void InitAnimations();

	virtual void InitTextures();

	virtual void InitPhysics();

	virtual void SetPosition(FVector3 _Position);

	virtual void BindKeys();

public:
	void TakeDamage(float _fValue);

	float GetDamage() const;

protected:
	void DamageFlickerAnimation(float _fDeltaTime);

	void InterpolateDamageAnimation(float _fDeltaTime);

	void DecideAnimation();

	void CheckFalling();


protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	UActionComponent* ActionComponent;

	UAttributeComponent* AttributeComponent;

	UCameraComponent* CameraComponent;

	BP_HPWidget* HPWidget;

	float FlickerTimer;

	float GaugeInterpolateTimer;

	float LastInterpolatedHP;

	float LastInterpolatedMP;

	int HPFlickerIndex;
};

