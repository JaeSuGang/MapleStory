#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class FMaterial
{
	friend class URenderSubsystem;
	friend class URenderComponent;

public:
	enum class EBlendMode
	{
		Opaque,
		Transculent
	};

private:
	EBlendMode BlendMode;
	int PSShaderID;
	int TextureID;
};

