#include "EnginePch.h"
#include "PhysicsCore/PhysicsSubsystem.h"

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

bool UPhysicsSubsystem::OverlapCallback(b2ShapeId _ID, void* _Context)
{
	vector<b2ShapeId>* pVector = reinterpret_cast<vector<b2ShapeId>*>(_Context);
	pVector->push_back(_ID);

	return true;
}