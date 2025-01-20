#pragma once
#include "Actor\Actor.h"

class URenderComponent;

class ADamageFont : public AActor
{
	typedef AActor Super;
public:
	/* 생성자와 오버라이드 */
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

