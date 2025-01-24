#pragma once
#include "Actor/Actor.h"

class URenderComponent;
class UPhysicsComponent;

class AAtomBase : public AActor
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	AAtomBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

	void SetPosition(FVector3 _Position) override;

	void SetRotation(FVector3 _Rotation) override;

	void AddZRotation(float _ZRotation) override;

	virtual void InitTexture();

	virtual void InitAnimations();

	virtual void InitPhysics();

	virtual bool FindTarget(float _fRadius);


public:

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	vector<AActor*> TempActorsVector;

	vector<UPhysicsComponent*> TempPhysicsComponentVector;

	weak_ptr<AActor> Target;

	bool IsHit;

	float LifeTime;

	float ElapsedTime;

	float FindTargetCooldown;
};

