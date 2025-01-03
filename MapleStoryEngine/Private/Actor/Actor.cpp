#include "EnginePch.h"
#include "World/World.h"
#include "Actor/Actor.h"

AActor::AActor()
{
	Transform.Scale = { 1.0f, 1.0f, 1.0f };
	Transform.Position = { };
	Transform.Rotation = { };
}

void AActor::Destroy()
{
	World->DestroyActor(this);
}

UWorld* AActor::GetWorld()
{
	return World;
}

ENGINE_API void AActor::SetWorld(UWorld* pWorld)
{
	this->World = pWorld;
}

ENGINE_API void AActor::SetScale(float x, float y, float z)
{
	Transform.Scale.x = x;
	Transform.Scale.y = y;
	Transform.Scale.z = z;
}

ENGINE_API FTransform& AActor::GetTransform()
{
	return Transform;
}
