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

	virtual void InitTexture();

	virtual void InitAnimations();

	virtual void InitPhysics();

public:

protected:
	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;

	vector<AActor*> OverlappedActors;

	bool IsHit;

	float LifeTime;

	float ElapsedTime;
};

