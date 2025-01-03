#pragma once
#include "EnginePch.h"

class UTexture
{
public:
	ComPtr<ID3D11Texture2D> Texture;
	ComPtr<ID3D11ShaderResourceView> SRV;
	unsigned Width;
	unsigned Height;
};

