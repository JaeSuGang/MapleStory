#pragma once
#include "ActorComponent/ActorComponent.h"
#include "Math/Transform.h"
#include "RenderSystem/Material.h"

struct FMesh;

class UMaterial;
class UAnimation;

class URenderComponent : public UActorComponent
{
	friend class URenderSubsystem;
	friend class UMaterial;

	typedef UActorComponent Super;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API URenderComponent();

	void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetAnimation(shared_ptr<UAnimation> _Animation);

	ENGINE_API void SetMaterial(shared_ptr<UMaterial> _Material);

	ENGINE_API void SetActorScaleByTextureSize();

	ENGINE_API void SetBlendMode(bool bIsTransculent);

	ENGINE_API void SetPixelShaderByName(string strShaderName);

	ENGINE_API void SetTextureByName(string strTextureName);

	ENGINE_API void SetMeshIDByName(string strName);

	void SetMaterialIfNull();

private:
	shared_ptr<UAnimation> Animation;
	shared_ptr<UMaterial> Material;
	int MeshID;
};
