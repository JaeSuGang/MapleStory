#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class AHitEffect : public AActor
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	AHitEffect();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	void SetAnimation(string strPath);

protected:
	URenderComponent* RenderComponent;
};

