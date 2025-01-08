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
	/* �����ڿ� �������̵� */
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

