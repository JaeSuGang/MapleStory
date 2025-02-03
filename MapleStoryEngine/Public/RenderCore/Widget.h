#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "Math/Vector3.h"

class UMaterial;

struct FWidgetSubImage
{
	shared_ptr<UMaterial> Material;
	FVector3 Position;
	FVector3 Size;
};

class UWidget : public UObject
{
	friend class URenderSubsystem;

	typedef UObject Super;

public:
	ENGINE_API int AddSubImageByTextureName(string _Name, FVector3 _Pos, FVector3 _Size);

protected:
	vector<FWidgetSubImage> SubImages;
};

