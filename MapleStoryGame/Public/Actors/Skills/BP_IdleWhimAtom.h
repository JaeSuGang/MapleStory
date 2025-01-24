#pragma once
#include "AtomBase.h"

class BP_IdleWhimAtom : public AAtomBase
{
	typedef AAtomBase Super;

public:
	BP_IdleWhimAtom();

	void Tick(float fDeltaTime);

	void BeginPlay() override;

	void InitTexture() override;

	void InitAnimations() override;

	void InitPhysics() override;

};

