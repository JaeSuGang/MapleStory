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

public:
	void SetInstigator(AActor* _Instigator);

protected:
	AActor* Instigator;

	URenderComponent* RenderComponent;

	bool IsScreenSkill;
};

