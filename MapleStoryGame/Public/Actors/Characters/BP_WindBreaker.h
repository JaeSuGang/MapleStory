#pragma once
#include "Actors/Characters/CharacterBase.h"

class BP_WindBreaker : public ACharacterBase
{
	typedef ACharacterBase Super;

public:
	void InitActions() override;

	void InitAnimations() override;

	void InitTextures() override;

	void BindKeys() override;
};

