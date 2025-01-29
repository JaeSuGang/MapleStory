#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"
#include "Math/Vector3.h"

class UMaterial;

struct FWidgetSubImage
{
	shared_ptr<UMaterial> Material;
	FVector3 Position;
};

class UWidget : public UObject
{
	typedef UObject Super;

public:
	void AddSubImageByTextureName(string _Name, FVector3 _Pos);

protected:
	vector<FWidgetSubImage> SubImages;
};

