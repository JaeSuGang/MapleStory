#include "EnginePch.h"
#include "RenderCore/Material.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"

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
