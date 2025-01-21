#pragma once
#include "ActorComponent/ActorComponent.h"
#include "Math/Transform.h"
#include "RenderCore/Material.h"
#include "RenderCore/Animation.h"



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

	void BeginPlay() override;

	void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void AddAnimationEvent(EAnimationName _AnimationName, int _Sequence, std::function<void()> _Function);

	ENGINE_API void AddAnimationEvent(FAnimationEvent _AnimationEvent);

	ENGINE_API bool GetHasPassedLastFrame() const;

	ENGINE_API EAnimationName GetCurrentAnimation() const;

	ENGINE_API void SetCurrentAnimation(EAnimationName Name);

	ENGINE_API void AddAnimationByFolder(EAnimationName Name, string strFolderPath, int nTimePerFrame);

	ENGINE_API void PlayAnimation(float fDeltaTime);

	ENGINE_API void EnableAnimation();

	ENGINE_API void EnableMaterial();

	ENGINE_API void SetActorScaleByTextureSize();

	ENGINE_API void SetBlendMode(bool bIsTransculent);

	ENGINE_API void SetPixelShaderByName(string strShaderName);

	ENGINE_API void SetTextureByName(string strTextureName);

	ENGINE_API void SetMeshIDByName(string strName);
	
	ENGINE_API int GetSortingLayer() const;

	ENGINE_API int GetZValue() const;

	ENGINE_API int GetZIndex() const;

	ENGINE_API void SetSortingLayer(int nLayer);

	ENGINE_API void SetZValue(int nZValue);

	ENGINE_API void SetZIndex(int nZIndex);

	void EnableMaterialIfNot();

private:
	shared_ptr<UAnimation> Animation;
	shared_ptr<UMaterial> Material;
	int SortingLayer;
	int ZValue;
	int ZIndex;
	int MeshID;
	bool IsVisible;

};
