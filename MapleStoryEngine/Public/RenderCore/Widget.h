#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "Math/Vector3.h"

class UWidget : public UObject
{
	typedef UObject Super;

public:
	ENGINE_API void SetPSShaderID(int _ID);

	ENGINE_API void SetTextureID(int _ID);

	ENGINE_API int GetPSShaderID() const;

	ENGINE_API int GetTextureID() const;

	ENGINE_API FVector3 GetPosition() const;

	ENGINE_API FVector3 GetSize() const;

	ENGINE_API void SetPosition(FVector3 _Pos);

	ENGINE_API void SetSize(FVector3 _Size);


protected:
	FVector3 Position;

	FVector3 Size;

	int TextureID;

	int PSShaderID;
};

