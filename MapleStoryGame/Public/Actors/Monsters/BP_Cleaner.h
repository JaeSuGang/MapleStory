#pragma once
#include "MobBase.h"

class BP_Cleaner : public AMobBase
{
	typedef AMobBase Super;

public:
	void InitAttributes() override;

	void InitTexture() override;

	void InitAnimations() override;

	void InitActions() override;
};

