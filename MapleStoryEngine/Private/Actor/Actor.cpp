#include "EnginePch.h"
#include "Actor/Actor.h"

AActor::AActor()
{
	Transform.Scale = { 1.0f, 1.0f, 1.0f };
	Transform.Position = { };
	Transform.Rotation = { };
}

ENGINE_API FTransform& AActor::GetTransform()
{
	return Transform;
}
