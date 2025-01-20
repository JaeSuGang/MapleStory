#pragma once
#include "Actor\Actor.h"

class URenderComponent;

class ADamageFont : public AActor
{
	typedef AActor Super;
public:
	/* �����ڿ� �������̵� */
	ADamageFont();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	void SetNumber(int nNum);

protected:
	URenderComponent* RenderComponent;

	float RemainedLifeTime;

	int Number;
};

