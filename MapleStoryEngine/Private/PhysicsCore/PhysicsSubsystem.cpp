#include "EnginePch.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Math/Transform.h"
#include "Math/Math.h"
#include "Actor/Actor.h"

UPhysicsSubsystem::~UPhysicsSubsystem()
{
	b2DestroyWorld(B2WorldID);

}

void UPhysicsSubsystem::Tick(float fDeltaTime)
{
	AccumulatedDeltaTime += fDeltaTime;

	if (AccumulatedDeltaTime < SimulationFrequencyTime)
		return;

	b2World_Step(this->B2WorldID, SimulationFrequencyTime, 4);

	AccumulatedDeltaTime -= SimulationFrequencyTime;
}

void UPhysicsSubsystem::LateInit()
{
	b2WorldDef WorldDef = b2DefaultWorldDef();

	WorldDef.gravity = { 0.0f, -40.0f };

	/* World ¼³Á¤ */
	B2WorldID = b2CreateWorld(&WorldDef);
}

UPhysicsComponent* UPhysicsSubsystem::GetPhysicsComponentByShapeId(b2ShapeId _ShapeId)
{
	return reinterpret_cast<UPhysicsComponent*>(b2Body_GetUserData(b2Shape_GetBody(_ShapeId)));
}

b2WorldId UPhysicsSubsystem::GetB2WorldID() const
{
	return B2WorldID;
}

UPhysicsComponent* UPhysicsSubsystem::GetPhysicsComponentByShapeID(b2ShapeId _ShapeId)
{
	return reinterpret_cast<UPhysicsComponent*>(b2Body_GetUserData(b2Shape_GetBody(_ShapeId)));
}

void UPhysicsSubsystem::FetchCapsuleOverlap(b2Capsule Capsule, b2Transform CapsulePos, b2QueryFilter Filter, vector<b2ShapeId>* pVector)
{
	CapsulePos.q.s = 0;
	CapsulePos.q.c = 1;
	b2World_OverlapCapsule(B2WorldID, &Capsule, CapsulePos, Filter, &UPhysicsSubsystem::OverlapCallback, pVector);
}

void UPhysicsSubsystem::FetchPlaneActorOverlap(AActor* _Actor, b2QueryFilter Filter, vector<b2ShapeId>* pReturnShapeIds)
{
	pReturnShapeIds->clear();

	FTransform _Transform = _Actor->GetTransform();

	b2Vec2 _B2Center{};
	b2Rot _B2Rot{ std::cos(DegreeToRadian(_Transform.Rotation.z)), std::sin(DegreeToRadian(_Transform.Rotation.z)) };

	b2Polygon Box = b2MakeOffsetBox(_Transform.Scale.x / 2.0f * PIXEL_TO_METER_CONSTANT, _Transform.Scale.y / 2.0f * PIXEL_TO_METER_CONSTANT, _B2Center, _B2Rot);

	this->FetchPolygonOverlap(Box, _Transform, Filter, pReturnShapeIds);
}

void UPhysicsSubsystem::FetchPolygonOverlap(b2Polygon _Polygon, FTransform Transform, b2QueryFilter Filter, vector<b2ShapeId>* pReturnShapeIds)
{
	b2Vec2 Vec{ Transform.Position.x * PIXEL_TO_METER_CONSTANT, Transform.Position.y * PIXEL_TO_METER_CONSTANT };
	b2Rot Rot{ std::cos(DegreeToRadian(Transform.Rotation.z)), std::sin(DegreeToRadian(Transform.Rotation.z)) };
	b2Transform b2Transform{ Vec, Rot };
	b2World_OverlapPolygon(B2WorldID, &_Polygon, b2Transform, Filter, &UPhysicsSubsystem::OverlapCallback, pReturnShapeIds);
}

void UPhysicsSubsystem::FetchAABBOverlap(float fWidth, float fHeight, FTransform Transform, b2QueryFilter Filter, vector<b2ShapeId>* pReturnShapeIds)
{
	b2Polygon Box = b2MakeBox(fWidth / 2.0f * PIXEL_TO_METER_CONSTANT, fHeight / 2.0f * PIXEL_TO_METER_CONSTANT);
	b2Vec2 Vec{ Transform.Position.x * PIXEL_TO_METER_CONSTANT, Transform.Position.y * PIXEL_TO_METER_CONSTANT };
	b2Rot Rot{ std::cos(DegreeToRadian(Transform.Rotation.z)), std::sin(DegreeToRadian(Transform.Rotation.z)) };
	b2Transform b2Transform{ Vec, Rot};
	b2World_OverlapPolygon(B2WorldID, &Box, b2Transform, Filter, &UPhysicsSubsystem::OverlapCallback, pReturnShapeIds);
}

bool UPhysicsSubsystem::OverlapCallback(b2ShapeId _ID, void* _Context)
{
	vector<b2ShapeId>* pVector = reinterpret_cast<vector<b2ShapeId>*>(_Context);
	pVector->push_back(_ID);

	return true;
}