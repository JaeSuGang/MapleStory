#pragma once
#include "Actor/Actor.h"

class URenderComponent;

class AObjBase : public AActor
{
	friend class UMapBase;

	typedef AActor Super;

public:
	enum class EObjType
	{
		Obj,
		Back,
		Foothold
	};

public:
	/* 생성자와 오버라이드 */
	AObjBase();

	virtual void BeginPlay();

	virtual void Tick(float fDeltaTime);

public:
	void SetObjType(EObjType _ObjType);

protected:
	EObjType ObjType;

	URenderComponent* RenderComponent;

	float OriginalX;

	float OriginalY;

	float cx;

	float cy;
};

