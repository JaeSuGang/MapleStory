#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class UMaterial : UObject
{
	friend class URenderSubsystem;
	friend class URenderComponent;
	friend class UAnimation;

public:
	enum class EBlendMode
	{
		Opaque,
		Transculent
	};

public:
	/* 생성자와 오버라이드 */
	ENGINE_API UMaterial() = default;

public:
	ENGINE_API void SetBlendMode(bool bIsTransculent);

	ENGINE_API void SetPixelShaderByName(string strShaderName);

	ENGINE_API void SetTextureByName(string strTextureName);

private:
	EBlendMode BlendMode;
	int PSShaderID;
	int TextureID;
};

