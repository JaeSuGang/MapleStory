#pragma once
#include "AtomBase.h"

class BP_HowlingGaleBall : public AAtomBase
{
	typedef AAtomBase Super;

public:
	BP_HowlingGaleBall();

	void Tick(float fDeltaTime);

	void BeginPlay() override;

	void InitTexture() override;

	void InitAnimations() override;

	void InitPhysics() override;


protected:
	float XVelocity;
};

