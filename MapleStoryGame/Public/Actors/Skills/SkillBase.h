#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class ASkillBase : public AActor 
{
	typedef AActor Super;

public:
	/* 생성자와 오버라이드 */
	ASkillBase();

	virtual void BeginPlay();

	virtual void Tick(float fDeltaTime);

	virtual void InitAttributes();

	virtual void InitTexture() = 0;

	virtual void InitAnimations() = 0;

	virtual void InitActions();

public:
	void SetInstigator(AActor* _Instigator);

	void SetPositionRelativeToInstigator(float fLeft, float fUp);

protected:
	AActor* Instigator;

	URenderComponent* RenderComponent;

	bool IsScreenSkill;
};

