#pragma once
#include "ActorComponent.h"
#include "Math/Transform.h"
#include "Material/Material.h"

struct FMesh;
class FMaterial;

class URenderComponent : public UActorComponent
{
	friend class URenderSubsystem;

	typedef UActorComponent Super;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API URenderComponent();

	void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetActorScaleByTextureSize();

	ENGINE_API void SetBlendMode(bool bIsTransculent);

	ENGINE_API void SetPixelShaderByName(string strShaderName);

	ENGINE_API void SetTextureByName(string strShaderName);

	ENGINE_API void SetMaterial(FMaterial MaterialToApply);

	ENGINE_API void SetMeshIDByName(string strName);


private:
	FMaterial Material;
	int MeshID;
};
