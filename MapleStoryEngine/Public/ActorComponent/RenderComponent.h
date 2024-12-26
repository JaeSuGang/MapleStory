#pragma once
#include "ActorComponent.h"
#include "Math/Transform.h"

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* �����ڿ� �������̵� */
	ENGINE_API URenderComponent() = default;
	void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void SetMeshName(string NewMeshName);

private:
	string MeshName;
};
