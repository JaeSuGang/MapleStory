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
	ENGINE_API UMaterial();

public:
	ENGINE_API void SetBlendMode(bool bIsTransculent);

	ENGINE_API void SetPixelShaderByName(string strShaderName);

	ENGINE_API void SetTextureByName(string strTextureName);

	ENGINE_API float GetAlphaValue() const;

	ENGINE_API void SetAlphaValue(float _Val);

	ENGINE_API void AddAlphaValue(float _Val);

private:
	EBlendMode BlendMode;
	float AlphaValue;
	int PSShaderID;
	int TextureID;
	int WidthTileCount;
	int HeightTileCount;
};

