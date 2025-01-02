#pragma once
#include "ActorComponent.h"
#include "Math/Transform.h"

struct FMesh;

class URenderComponent : public UActorComponent
{
	friend class URenderSubsystem;

	typedef UActorComponent Super;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API URenderComponent();
	void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetMeshInfosByName(string strName);
	ENGINE_API void SetTextureInfosByName(string strName);

	ENGINE_API void SetSRVIDByName(string strName);
	ENGINE_API void SetTextureIDByName(string strName);
	ENGINE_API void SetMeshIDByName(string strName);
	ENGINE_API void SetVertexBufferIDByName(string strName);
	ENGINE_API void SetIndexBufferIDByName(string strName);


private:
	int MeshID;
	int VertexBufferID;
	int IndexBufferID;
	int TextureID;
	int SRVID;
};
