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

	WorldDef.gravity = { 0.0f, -98.0f };

	/* World ¼³Á¤ */
	B2WorldID = b2CreateWorld(&WorldDef);
}
