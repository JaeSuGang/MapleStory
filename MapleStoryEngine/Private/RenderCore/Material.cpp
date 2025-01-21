#include "EnginePch.h"
#include "RenderCore/Material.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"

UMaterial::UMaterial()
{
	BlendMode = EBlendMode::Opaque;
	AlphaValue = 1.0f;
	PSShaderID = 0;
	TextureID = 0;
	WidthTileLength = 1;
	HeightTileLength = 1;
}

void UMaterial::SetBlendMode(bool bIsTransculent)
{
	if (bIsTransculent == false)
		BlendMode = UMaterial::EBlendMode::Opaque;

	if (bIsTransculent == true)
		BlendMode = UMaterial::EBlendMode::Transculent;
}

void UMaterial::SetPixelShaderByName(string strShaderName)
{
	PSShaderID = GEngine->RenderSubsystem->GetPixelShaderIDByName(strShaderName);
}

void UMaterial::SetTextureByName(string strTextureName)
{
	TextureID = GEngine->RenderSubsystem->GetTextureIDByName(strTextureName);
}

float UMaterial::GetAlphaValue() const
{
	return AlphaValue;
}

void UMaterial::SetAlphaValue(float _Val)
{
	AlphaValue = _Val;
}

void UMaterial::AddAlphaValue(float _Val)
{
	AlphaValue += _Val;
}