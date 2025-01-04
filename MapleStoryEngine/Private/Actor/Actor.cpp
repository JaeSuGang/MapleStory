#include "EnginePch.h"
#include "World/World.h"
#include "Actor/Actor.h"

AActor::AActor()
	:
	Transform{}
{
	World = nullptr;
	IsBeginPlayed = false;

	Transform.Scale = { 1.0f, 1.0f, 1.0f };
	Transform.Position = { };
	Transform.Rotation = { };
}

void AActor::BeginPlay()
{
	this->IsBeginPlayed = true;
}

void AActor::Tick(float fDeltaTime)
{

}

void AActor::Destroy()
{
	World->DestroyActor(this);
}

UWorld* AActor::GetWorld() const
{
	return World;
}

bool AActor::GetIsBeginPlayed() const
{
	return IsBeginPlayed;
}

void AActor::SetWorld(UWorld* pWorld)
{
	this->World = pWorld;
}

void AActor::SetScale(float x, float y, float z)
{
	Transform.Scale.x = x;
	Transform.Scale.y = y;
	Transform.Scale.z = z;
}

FTransform& AActor::GetTransform()
{
	return Transform;
}
