#include "EnginePch.h"
#include "World/World.h"
#include "Actor/Actor.h"
#include "ActorComponent/ActorComponent.h"
#include "GameplayTags/GameplayTagContainer.h"

AActor::AActor()
	:
	Transform{},
	IsTickEnabled{true}
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

	for (auto Pair : OwnedComponents)
	{
		UActorComponent* Component = Pair.second.get();

		Component->BeginPlay();
	}
}

void AActor::Tick(float fDeltaTime)
{
	for (auto Pair : OwnedComponents)
	{
		UActorComponent* Component = Pair.second.get();

		Component->TickComponent(fDeltaTime);
	}
}

void AActor::LateTick(float fDeltaTime)
{

}

bool AActor::HasTagExact(FGameplayTag& _Tag) const
{
	return TagContainer.HasTagExact(_Tag);
}

bool AActor::HasTagExact(string _Name) const
{
	return TagContainer.HasTagExact(_Name);
}

bool AActor::GetIsTickEnabled() const
{
	return IsTickEnabled;
}

void AActor::SetIsTickEnabled(bool bValue)
{
	IsTickEnabled = bValue;
}

void AActor::SetPosition(FVector3 _Position)
{
	Transform.Position = _Position;
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

void AActor::MultiplyScale(float x, float y, float z)
{
	Transform.Scale.x *= x;
	Transform.Scale.y *= y;
	Transform.Scale.z *= z;
}

void AActor::SetRotation(FVector3 _Vector)
{
	Transform.Rotation.x = _Vector.x;
	Transform.Rotation.y = _Vector.y;
	Transform.Rotation.z = _Vector.z;
}

void AActor::SetScale(FVector3 _Vector)
{
	Transform.Scale.x = _Vector.x;
	Transform.Scale.y = _Vector.y;
	Transform.Scale.z = _Vector.z;
}

FTransform& AActor::GetTransform()
{
	return Transform;
}
