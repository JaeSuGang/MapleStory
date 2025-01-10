#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class ASkillBase : public AActor 
{
	typedef AActor Super;

public:
	/* �����ڿ� �������̵� */
	ASkillBase();

	virtual void BeginPlay() = 0;

	virtual void Tick(float fDeltaTime) = 0;

protected:
	URenderComponent* RenderComponent;

	bool IsScreenSkill;
};

