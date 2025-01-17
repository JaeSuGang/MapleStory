#pragma once
#include "World/WorldSubsystem.h"
#include "Math/Transform.h"

class UPhysicsSubsystem : public UWorldSubsystem
{
	friend class UPhysicsComponent;

public:
	/* �����ڿ� �������̵� */
	~UPhysicsSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API b2WorldId GetB2WorldID() const;

	ENGINE_API UPhysicsComponent* GetPhysicsComponentByShapeID(b2ShapeId _ShapeId);

	ENGINE_API void FetchCapsuleOverlap(b2Capsule Capsule, b2Transform CapsulePos, b2QueryFilter Filter, vector<b2ShapeId>* pReturnShapeIds);

	ENGINE_API void FetchBoxOverlap(float fWidth, float fHeight, FTransform Transform, b2QueryFilter Filter, vector<b2ShapeId>* pReturnShapeIds);

public:
	static bool OverlapCallback(b2ShapeId _ID, void* _Context);

protected:
	b2WorldId B2WorldID;

	const float SimulationFrequencyTime = 1.0f / 60.0f;

	float AccumulatedDeltaTime;
};

