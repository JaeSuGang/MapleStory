#include "EnginePch.h"
#include "World/PhysicsSubsystem.h"

UPhysicsSubsystem::~UPhysicsSubsystem()
{
	b2DestroyWorld(B2WorldID);
}

void UPhysicsSubsystem::Tick(float fDeltaTime)
{

}

void UPhysicsSubsystem::LateInit()
{
	b2WorldDef WorldDef = b2DefaultWorldDef();

	/* World ¼³Á¤ */

	B2WorldID = b2CreateWorld(&WorldDef);
}
