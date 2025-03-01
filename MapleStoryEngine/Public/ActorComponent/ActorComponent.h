#pragma once
#include "UObject/Object.h"
#include "EnginePch.h"

class AActor;

class UActorComponent : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API virtual void BeginPlay() = 0;

	ENGINE_API virtual void TickComponent(float fDeltaTime) = 0;

public:
	ENGINE_API void SetOwner(AActor* pOwner);

	ENGINE_API AActor* GetOwner() const;

protected:
	AActor* Owner;
};

