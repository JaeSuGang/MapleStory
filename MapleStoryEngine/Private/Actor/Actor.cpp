#include "EnginePch.h"
#include "Actor/Actor.h"

AActor::AActor()
{
	Transform.Scale = { 1.0f, 1.0f, 1.0f };
	Transform.Position = { };
	Transform.Rotation = { };
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
