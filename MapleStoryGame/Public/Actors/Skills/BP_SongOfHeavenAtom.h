#pragma once
#include "AtomBase.h"

class BP_SongOfHeavenAtom : public AAtomBase
{
	typedef AAtomBase Super;

public:
	BP_SongOfHeavenAtom();

	void Tick(float fDeltaTime);

	void BeginPlay() override;

	void InitTexture() override;

	void InitAnimations() override;

	void InitPhysics() override;
};

