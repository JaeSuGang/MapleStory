#pragma once
#include "AtomBase.h"

class BP_MistralSpringAtom0 : public AAtomBase
{
	typedef AAtomBase Super;

public:
	BP_MistralSpringAtom0();

	void Tick(float fDeltaTime);

	void BeginPlay() override;

	void InitTexture() override;

	void InitAnimations() override;

	void InitPhysics() override;

protected:
	bool HasShot;
};

