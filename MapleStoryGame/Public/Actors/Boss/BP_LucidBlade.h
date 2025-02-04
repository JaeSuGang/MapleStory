#pragma once
#include "Actors/Skills/AtomBase.h"

class BP_LucidBlade : public AAtomBase
{
	typedef AAtomBase Super;

public:
	BP_LucidBlade();

	void Tick(float fDeltaTime);

	void BeginPlay() override;

	void InitTexture() override;

	void InitAnimations() override;

	void InitPhysics() override;

protected:
	vector<AActor*> AlreadyHitActors;
};

