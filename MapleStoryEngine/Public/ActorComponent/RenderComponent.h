#pragma once
#include "ActorComponent.h"
#include "Math/Transform.h"

struct FMesh;

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* �����ڿ� �������̵� */
	ENGINE_API URenderComponent();
	void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetTextureName(const char* lpszNewName);
	ENGINE_API const char* GetTextureName();
	ENGINE_API void SetMeshName(const char* lpszNewName);
	ENGINE_API const char* GetMeshName();

private:
	string MeshName;
	string TextureName;
};
